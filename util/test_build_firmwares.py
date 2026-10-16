#!/usr/bin/env python3
"""Check the firmware build script without compiling or updating submodules."""

import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest


SCRIPT = Path(__file__).resolve().parents[1] / 'build_firmwares.sh'
TARGETS = [
    ('converter/ibm_5140', 'default'),
    ('converter/ibm_5140', 'razerban'),
    ('converter/ibm_5140', 'via'),
    ('converter/ibm_pingmaster', 'default'),
    ('converter/ibm_pingmaster', 'razerban'),
    ('converter/citoh', 'default'),
    ('converter/citoh', 'via'),
    ('razerban/andromeda', 'default'),
    ('razerban/andromeda', 'via'),
]


class BuildFirmwareTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix='qmk-build-test-')
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.script = self.root / SCRIPT.name
        shutil.copy2(SCRIPT, self.script)
        self.log = self.root / 'calls'
        self.bin = self.root / 'bin'
        self.bin.mkdir()
        for keyboard, keymap in TARGETS:
            board = self.root / 'keyboards' / keyboard
            directory = board / 'keymaps' / keymap
            directory.mkdir(parents=True, exist_ok=True)
            (board / 'keyboard.json').write_text('{}')
            (directory / 'keymap.c').write_text('')
        for name in ('git', 'qmk'):
            tool = self.bin / name
            tool.write_text('''#!/bin/bash
printf '%s|%s|%s|%s\\n' "${0##*/}" "$PWD" "$QMK_HOME" "$*" >> "$CALL_LOG"
if [[ "$*" == *"${FAIL_MATCH:-__never__}"* ]]; then exit 7; fi
if [[ "${0##*/}" == qmk && "$*" != *--dry-run* && "${SKIP_ARTIFACT:-0}" != 1 ]]; then
    keyboard=$3
    keymap=$5
    extension=hex
    if [[ "$keyboard" == razerban/andromeda ]]; then extension=uf2; fi
    printf '' > "${keyboard//\\//_}_${keymap}.$extension"
fi
''')
            tool.chmod(0o755)
        self.env = dict(os.environ, PATH=f'{self.bin}:{os.environ["PATH"]}',
                        CALL_LOG=str(self.log), QMK_HOME='/another/checkout', JOBS='1')
        self.env.pop('FAIL_MATCH', None)
        self.env.pop('SKIP_ARTIFACT', None)

    def run_script(self, *arguments):
        return subprocess.run([str(self.script), *arguments], cwd='/tmp', env=self.env,
                              capture_output=True, text=True, timeout=10)

    def calls(self):
        return self.log.read_text().splitlines() if self.log.exists() else []

    def test_default_builds_all_targets_from_the_script_checkout(self):
        result = self.run_script()
        self.assertEqual(result.returncode, 0, result.stderr)
        calls = [line.split('|') for line in self.calls()]
        self.assertEqual(calls[0][0::3], ['git', 'submodule sync --recursive'])
        self.assertEqual(calls[1][0::3], ['git', 'submodule update --init --recursive'])
        self.assertEqual(len(calls), 11)
        for call, (keyboard, keymap) in zip(calls[2:], TARGETS):
            self.assertEqual(call[:3], ['qmk', str(self.root), str(self.root)])
            self.assertEqual(call[3], f'compile -kb {keyboard} -km {keymap} --parallel 1 -e SKIP_GIT=yes')

    def test_clean_parallel_offline_build(self):
        result = self.run_script('--skip-submodules', '--clean', '-j', '8')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.calls()), 9)
        self.assertTrue(all('--parallel 8' in call and '--clean' in call for call in self.calls()))
        self.assertTrue(all(call.startswith('qmk|') for call in self.calls()))

    def test_dry_run_does_not_update_submodules(self):
        result = self.run_script('--dry-run')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.calls()), 9)
        self.assertTrue(all('--dry-run' in call for call in self.calls()))

    def test_setup_failure_stops_before_compiling(self):
        self.env['FAIL_MATCH'] = 'submodule update'
        result = self.run_script()
        self.assertEqual(result.returncode, 7)
        self.assertEqual(len(self.calls()), 2)
        self.assertIn('submodule setup failed', result.stderr)

    def test_sync_failure_stops_before_updating(self):
        self.env['FAIL_MATCH'] = 'submodule sync'
        result = self.run_script()
        self.assertEqual(result.returncode, 7)
        self.assertEqual(len(self.calls()), 1)
        self.assertIn('submodule setup failed', result.stderr)

    def test_compile_failure_identifies_target_and_stops(self):
        self.env['FAIL_MATCH'] = '-kb converter/ibm_pingmaster -km default'
        result = self.run_script('--skip-submodules')
        self.assertEqual(result.returncode, 7)
        self.assertEqual(len(self.calls()), 4)
        self.assertIn('converter/ibm_pingmaster:default failed', result.stderr)

    def test_missing_late_target_stops_before_setup(self):
        (self.root / 'keyboards/razerban/andromeda/keymaps/via/keymap.c').unlink()
        result = self.run_script()
        self.assertEqual(result.returncode, 1)
        self.assertEqual(self.calls(), [])
        self.assertIn('razerban/andromeda:via', result.stderr)

    def test_bad_options_fail_without_side_effects(self):
        for arguments in (['--jobs'], ['--jobs', '0'], ['--jobs', '-1'],
                          ['--jobs', 'abc'], ['--unknown']):
            with self.subTest(arguments=arguments):
                self.assertEqual(self.run_script(*arguments).returncode, 2)
                self.assertEqual(self.calls(), [])

    def test_help_does_not_build(self):
        result = self.run_script('--help')
        self.assertEqual(result.returncode, 0)
        self.assertIn('Usage:', result.stdout)
        self.assertEqual(self.calls(), [])

    def test_jobs_environment_can_be_overridden(self):
        self.env['JOBS'] = '3'
        result = self.run_script('--skip-submodules', '--jobs', '5')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertTrue(all('--parallel 5' in call for call in self.calls()))

    def test_json_keymap_is_accepted(self):
        directory = self.root / 'keyboards/razerban/andromeda/keymaps/via'
        (directory / 'keymap.c').unlink()
        (directory / 'keymap.json').write_text('{}')
        result = self.run_script('--skip-submodules')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.calls()), 9)

    def test_missing_qmk_has_a_clear_error(self):
        (self.bin / 'qmk').unlink()
        (self.bin / 'dirname').symlink_to(shutil.which('dirname'))
        self.env['PATH'] = str(self.bin)
        result = self.run_script('--skip-submodules')
        self.assertEqual(result.returncode, 1)
        self.assertIn('qmk is not installed', result.stderr)
        self.assertEqual(self.calls(), [])

    def test_keymap_selectors_build_and_list_only_matching_targets(self):
        for selector in ('all', 'default', 'razerban', 'via'):
            with self.subTest(selector=selector):
                self.log.write_text('')
                result = self.run_script(selector, '--skip-submodules')
                self.assertEqual(result.returncode, 0, result.stderr)
                selected = [(kb, km) for kb, km in TARGETS if selector == 'all' or km == selector]
                self.assertEqual(len(self.calls()), len(selected))
                summary = result.stdout.split('Firmware files:\n')[1].splitlines()
                expected = []
                for keyboard, keymap in selected:
                    extension = 'uf2' if keyboard == 'razerban/andromeda' else 'hex'
                    expected.append(str(self.root / f'{keyboard.replace("/", "_")}_{keymap}.{extension}'))
                self.assertEqual([line.strip() for line in summary], expected)

    def test_multiple_selectors_and_vial_are_rejected(self):
        for arguments in (['all', 'via'], ['default', 'default'], ['vial']):
            with self.subTest(arguments=arguments):
                self.assertEqual(self.run_script(*arguments).returncode, 2)
                self.assertEqual(self.calls(), [])

    def test_unselected_missing_keymap_does_not_block_build(self):
        (self.root / 'keyboards/razerban/andromeda/keymaps/via/keymap.c').unlink()
        result = self.run_script('--skip-submodules', 'default')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.calls()), 4)

    def test_dry_run_does_not_claim_firmware_was_created(self):
        result = self.run_script('via', '--dry-run', '--clean')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.calls()), 3)
        self.assertNotIn('Firmware files:', result.stdout)
        self.assertEqual(list(self.root.glob('*.hex')) + list(self.root.glob('*.uf2')), [])

    def test_missing_firmware_stops_the_build(self):
        self.env['SKIP_ARTIFACT'] = '1'
        result = self.run_script('--skip-submodules', 'via')
        self.assertEqual(result.returncode, 1)
        self.assertEqual(len(self.calls()), 1)
        self.assertIn('converter/ibm_5140:via finished without creating', result.stderr)

    def test_git_is_required_only_when_updating_submodules(self):
        (self.bin / 'git').unlink()
        (self.bin / 'dirname').symlink_to(shutil.which('dirname'))
        self.env['PATH'] = str(self.bin)
        result = self.run_script()
        self.assertEqual(result.returncode, 1)
        self.assertIn('git is not installed', result.stderr)
        self.assertEqual(self.calls(), [])
        self.assertEqual(self.run_script('--skip-submodules', 'via').returncode, 0)
        self.assertEqual(self.run_script('--dry-run', 'via').returncode, 0)


if __name__ == '__main__':
    unittest.main()
