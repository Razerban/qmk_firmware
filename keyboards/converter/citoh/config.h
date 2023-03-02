/* Copyright 2021 Ahmed Abdelkafi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* key matrix size */
#define MATRIX_ROWS 16
#define MATRIX_COLS 8

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B7, D0, D1, D2, D3, D4, D5, D6, D7, E0, E1, C0, C1, C2, C3, C4 }
#define MATRIX_COL_PINS { B6, B5, B4, B3, B2, B1, B0, E7 }

#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN F0
#define LED_CAPS_LOCK_PIN F1
#define LED_SCROLL_LOCK_PIN F2
#define LED_PIN_ON_STATE 0 // The state of the indicator pins when the LED is "on" - 1 for high, 0 for low
