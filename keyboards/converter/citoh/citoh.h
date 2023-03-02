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

#include "quantum.h"

#define LAYOUT( \
    K27,      K34, K74, K76, K77,   KF7, KC7, KD6, KD4,    KF4, KF5, KA5, KB5,  K15, K13, K01,                      \
    K24, K25, K35, K75, K65, K64, K84, K85, KC5, KD5, K95, K94, KC4, KF6,       KB4, K04, KE4,  KA1, KB1, KE1, KE0, \
    K26,   K23, K33, K73, K63, K66, K86, K83, KC3, KD3, K93, K96, KC6,  KF1,    KA4, K05, KE5,  KA3, KB3, KE3, K03, \
    K36,    K22, K32, K72, K62, K67, K87, K82, KC2, KD2, K92, K97, KD7,                         KA6, KB6, KE6,      \
    K56,  K91, K21, K31, K71, K61, K60, K80, K81, KC1, KD1, K90,        K51,         K07,       KA2, KB2, KE2, K02, \
    K44,        K17,                  KF0,                 K10,        K41,     K00, KA0, KB0,  KB7,      KE7       \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   KC_NO, K07   }, \
    { K10,   KC_NO, KC_NO, K13,   KC_NO, K15,   KC_NO, K17   }, \
    { KC_NO, K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { KC_NO, K31,   K32,   K33,   K34,   K35,   K36,   KC_NO }, \
    { KC_NO, K41,   KC_NO, KC_NO, K44,   KC_NO, KC_NO, KC_NO }, \
    { KC_NO, K51,   KC_NO, KC_NO, KC_NO, KC_NO, K56,   KC_NO }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67   }, \
    { KC_NO, K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87   }, \
    { K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97   }, \
    { KA0,   KA1,   KA2,   KA3,   KA4,   KA5,   KA6,   KC_NO }, \
    { KB0,   KB1,   KB2,   KB3,   KB4,   KB5,   KB6,   KB7   }, \
    { KC_NO, KC1,   KC2,   KC3,   KC4,   KC5,   KC6,   KC7   }, \
    { KC_NO, KD1,   KD2,   KD3,   KD4,   KD5,   KD6,   KD7   }, \
    { KE0,   KE1,   KE2,   KE3,   KE4,   KE5,   KE6,   KE7   }, \
    { KF0,   KF1,   KC_NO, KC_NO, KF4,   KF5,   KF6,   KF7   }, \
}
