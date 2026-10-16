#!/bin/bash

set -euo pipefail

usage() {
  cat <<'USAGE'
Usage: build_firmwares.sh [options] [all|default|razerban|via]

Build all nine custom keyboard/keymap targets by default.
Select default (4 targets), razerban (2 targets), or via (3 targets).
Existing build files are reused unless --clean is supplied.

Options:
  -j, --jobs N          Parallel jobs per build (default: JOBS or 1)
  --clean               Clean each target before compiling
  --skip-submodules     Use the installed submodules without updating them
  -n, --dry-run         Validate and print build commands without building or updating
  -h, --help            Show this help
USAGE
}

jobs=${JOBS:-1}
clean=false
update_submodules=true
dry_run=false
selected_keymap=all
target_selected=false

while (( $# )); do
  case "$1" in
    -j|--jobs)
      if (( $# < 2 )); then
        printf 'Error: %s requires a job count.\n' "$1" >&2
        exit 2
      fi
      jobs=$2
      shift 2
      ;;
    --clean) clean=true; shift ;;
    --skip-submodules) update_submodules=false; shift ;;
    -n|--dry-run) dry_run=true; shift ;;
    -h|--help) usage; exit 0 ;;
    all|default|razerban|via)
      if $target_selected; then
        printf 'Error: select only one target: all, default, razerban, or via.\n' >&2
        exit 2
      fi
      selected_keymap=$1
      target_selected=true
      shift
      ;;
    *) printf 'Error: unknown argument: %s\n' "$1" >&2; usage >&2; exit 2 ;;
  esac
done

if [[ ! "$jobs" =~ ^[1-9][0-9]*$ ]]; then
  printf 'Error: jobs must be a positive integer.\n' >&2
  exit 2
fi

cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
# Ensure the CLI builds this fork even when another QMK home is configured.
export QMK_HOME="$PWD"

if ! command -v qmk >/dev/null 2>&1; then
  printf 'Error: qmk is not installed or is missing from PATH.\n' >&2
  exit 1
fi
if $update_submodules && ! $dry_run && ! command -v git >/dev/null 2>&1; then
  printf 'Error: git is not installed or is missing from PATH.\n' >&2
  exit 1
fi

all_targets=(
  converter/ibm_5140:default
  converter/ibm_5140:razerban
  converter/ibm_5140:via
  converter/ibm_pingmaster:default
  converter/ibm_pingmaster:razerban
  converter/citoh:default
  converter/citoh:via
  razerban/andromeda:default
  razerban/andromeda:via
)

targets=()
for target in "${all_targets[@]}"; do
  if [[ "$selected_keymap" == all || "${target##*:}" == "$selected_keymap" ]]; then
    targets+=("$target")
  fi
done

# Check every selected target before updating submodules or starting a build.
for target in "${targets[@]}"; do
  keyboard=${target%%:*}
  keymap=${target##*:}
  if [[ ! -f "keyboards/$keyboard/keyboard.json" ]] ||
     [[ ! -f "keyboards/$keyboard/keymaps/$keymap/keymap.c" &&
        ! -f "keyboards/$keyboard/keymaps/$keymap/keymap.json" ]]; then
    printf 'Error: missing keyboard metadata or keymap for %s.\n' "$target" >&2
    exit 1
  fi
done

current_step='submodule setup'
trap 'status=$?; printf "Error: %s failed (exit %s).\n" "$current_step" "$status" >&2; exit "$status"' ERR

if $update_submodules && ! $dry_run; then
  printf 'Updating submodules...\n'
  # This checkout's QMK helper does not propagate Git failures.
  git submodule sync --recursive
  git submodule update --init --recursive
fi

compile_args=(--parallel "$jobs" -e SKIP_GIT=yes)
if $clean; then compile_args+=(--clean); fi
if $dry_run; then compile_args+=(--dry-run); fi

index=0
firmware_files=()
for target in "${targets[@]}"; do
  index=$((index + 1))
  current_step=$target
  printf '\n[%s/%s] %s\n' "$index" "${#targets[@]}" "$target"
  qmk compile -kb "${target%%:*}" -km "${target##*:}" "${compile_args[@]}"
  if ! $dry_run; then
    keyboard=${target%%:*}
    keymap=${target##*:}
    # The three AVR converters produce HEX; the RP2040 Andromeda produces UF2.
    extension=hex
    if [[ "$keyboard" == razerban/andromeda ]]; then extension=uf2; fi
    firmware="$PWD/${keyboard//\//_}_${keymap}.$extension"
    if [[ ! -f "$firmware" ]]; then
      printf 'Error: %s finished without creating %s.\n' "$target" "$firmware" >&2
      exit 1
    fi
    firmware_files+=("$firmware")
  fi
done

if $dry_run; then
  printf '\nValidated all %s build commands.\n' "${#targets[@]}"
else
  printf '\nBuild complete (%s firmwares). Firmware files:\n' "${#targets[@]}"
  printf '  %s\n' "${firmware_files[@]}"
fi
