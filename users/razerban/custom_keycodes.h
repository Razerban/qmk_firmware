#pragma once

#define ESC_CTRL LCTL_T(KC_ESC)

// Useful portable shortcuts
// The most portable copy/paste keys
#define COPY      LCTL(KC_INS)
#define CUT       LSFT(KC_DEL)
#define PASTE     LSFT(KC_INS)

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    PREV_TAB = SAFE_RANGE,
    NEXT_TAB,
    OPEN_ALFRED,
    PREV_WORKSPACE,
    NEXT_WORKSPACE,
    PREV_WINDOW_WIN,
    NEXT_WINDOW_WIN,
    PREV_WINDOW_MAC,
    NEXT_WINDOW_MAC
};
