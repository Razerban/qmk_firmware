/*
Copyright 2022 Razerban
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* Matrix pins */
#define MATRIX_ROW_PINS { GP1, GP27, GP28, GP29, GP15, GP10 }
#define MATRIX_COL_PINS { GP26, GP25, GP24, GP23, GP22, GP21, GP20, GP19, GP18, GP17, GP14, GP13, GP12, GP11, GP4, GP3, GP2 }

/* Diode direction: COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Caps lock & Scroll Lock pins */
#define LED_CAPS_LOCK_PIN GP16
#define LED_SCROLL_LOCK_PIN GP0
#define LED_PIN_ON_STATE 1

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Use 1000hz polling */
#define USB_POLLING_INTERVAL_MS 1
