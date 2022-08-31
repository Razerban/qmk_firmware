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

#include "quantum.h"
#include "raw_hid.h"
#include "comm_protocol.h"
#include <string.h>

static const uint8_t protocolMagic[] = PROTOCOL_MAGIC;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (memcmp(data, protocolMagic, sizeof(protocolMagic)) != 0) {
        return;
    }

    // Prepare a buffer
    uint8_t response[RAW_EPSIZE];
    memcpy(response, protocolMagic, sizeof(protocolMagic));

    // Default return values is ERROR
    response[2] = ERROR;

    uint8_t command = data[2];
    switch (command) {
        case GET_VERSION:
            response[2] = OK;
            response[3] = PROTOCOL_VERSION_MAJOR;
            response[4] = PROTOCOL_VERSION_MID;
            response[5] = (PROTOCOL_VERSION_MINOR >> 8) & 0xff;
            response[6] = (PROTOCOL_VERSION_MINOR >> 0) & 0xff;
            break;
        case ENTER_BOOTLOADER:
            wait_ms(10);
            bootloader_jump();
            // we should not be reaching the following:
            wait_ms(10);
            response[2] = OK;
            break;
        default:
            break;
    }

    raw_hid_send(response, sizeof(response));
}
