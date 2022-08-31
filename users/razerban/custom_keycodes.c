#include "quantum.h"
#include "custom_keycodes.h"

bool is_alt_tab_active = false;
bool is_cmd_tab_active = false;
uint16_t alt_tab_timer = 0;
uint16_t cmd_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case PREV_TAB:
      if (record->event.pressed) {
        register_code(KC_LSFT);
        register_code(KC_LCTRL);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LCTRL);
        unregister_code(KC_LSFT);
      }
      break;
    case NEXT_TAB:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LCTRL);
      }
      break;
    case OPEN_ALFRED:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_SPC);
      } else {
        unregister_code(KC_SPC);
        unregister_code(KC_LGUI);
      }
      break;
    case PREV_WORKSPACE:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_LEFT);
      } else {
        unregister_code(KC_LEFT);
        unregister_code(KC_LCTRL);
      }
      break;
    case NEXT_WORKSPACE:
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_RIGHT);
      } else {
        unregister_code(KC_RGHT);
        unregister_code(KC_LCTRL);
      }
      break;
    case PREV_WINDOW_WIN:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
      break;
    case NEXT_WINDOW_WIN:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case PREV_WINDOW_MAC:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LGUI);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_LSFT);
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
      }
      break;
    case NEXT_WINDOW_MAC:
      if (record->event.pressed) {
        if (!is_cmd_tab_active) {
          is_cmd_tab_active = true;
          register_code(KC_LGUI);
        }
        cmd_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 1000) {
      unregister_code(KC_LGUI);
      is_cmd_tab_active = false;
    }
  }
}
