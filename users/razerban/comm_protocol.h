/* Copyright 2020 Ahmed Abdelkafi
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

#ifndef COMM_PROTOCOL_H
#define COMM_PROTOCOL_H

#if defined(KEYBOARD_SHARED_EP) && defined(RAW_ENABLE) // Kept as is to be compatible with Purea Andrei firmwares
#error "Enabling the KEYBOARD_SHARED_EP will make the util be unable to communicate with the firmware, due to hidapi limiations, the util can't figure out which interface to talk to, so it hardcodes interface zero."
#endif

#ifndef RAW_EPSIZE
#define RAW_EPSIZE 32
#endif

#define PROTOCOL_VERSION_MAJOR 2 // Kept as is to be compatible with Purea Andrei firmwares
#define PROTOCOL_VERSION_MID 0   // Kept as is to be compatible with Purea Andrei firmwares
#define PROTOCOL_VERSION_MINOR 4 // Kept as is to be compatible with Purea Andrei firmwares

#define PROTOCOL_MAGIC { 0x55, 0xAA } // Kept as is to be compatible with Purea Andrei firmwares

enum commands {
    GET_VERSION = 0x11,  // Kept as is to be compatible with Purea Andrei firmwares
    ENTER_BOOTLOADER
};

enum responses {
    OK = 0x22, // Kept as is to be compatible with Purea Andrei firmwares
    ERROR
};

#endif // COMM_PROTOCOL_H
