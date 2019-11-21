#/bin/bash

readonly LAYOUT_FILE="layout.json"

for i in $(seq 10)
do
    sed -i.bak -e's/FR_SUP2/KC_GRV/' -e's/FR_AMP/KC_1/' -e's/FR_EACU/KC_2/' -e's/FR_QUOT/KC_3/' -e's/FR_APOS/KC_4/' -e's/FR_LPRN/KC_5/' -e's/FR_MINS/KC_6/' -e's/FR_EGRV/KC_7/' -e's/FR_UNDS/KC_8/' -e's/FR_CCED/KC_9/' -e's/FR_AGRV/KC_0/' -e's/FR_RPRN/KC_MINS/' -e's/FR_EQL/KC_EQL/' -e's/FR_A/KC_Q/' -e's/FR_Z/KC_W/' -e's/FR_CIRC/KC_LBRC/' -e's/FR_DLR/KC_RBRC/' -e's/FR_Q/KC_A/' -e's/FR_M/KC_SCLN/' -e's/FR_UGRV/KC_QUOT/' -e's/FR_ASTR/KC_NUHS/' -e's/FR_LESS/KC_NUBS/' -e's/FR_W/KC_Z/' -e's/FR_COMM/KC_M/' -e's/FR_SCLN/KC_COMM/' -e's/FR_COLN/KC_DOT/' -e's/FR_EXLM/KC_SLSH/' -e's/FR_1/LSFT(KC_1)/' -e's/FR_2/LSFT(KC_2)/' -e's/FR_3/LSFT(KC_3)/' -e's/FR_4/LSFT(KC_4)/' -e's/FR_5/LSFT(KC_5)/' -e's/FR_6/LSFT(KC_6)/' -e's/FR_7/LSFT(KC_7)/' -e's/FR_8/LSFT(KC_8)/' -e's/FR_9/LSFT(KC_9)/' -e's/FR_0/LSFT(KC_0)/' -e's/FR_OVRR/LSFT(KC_MINS)/' -e's/FR_PLUS/LSFT(KC_EQL)/' -e's/FR_UMLT/LSFT(KC_LBRC)/' -e's/FR_PND/LSFT(KC_RBRC)/' -e's/FR_PERC/LSFT(KC_QUOT)/' -e's/FR_MU/LSFT(KC_NUHS)/' -e's/FR_GRTR/LSFT(KC_NUBS)/' -e's/FR_QUES/LSFT(KC_M)/' -e's/FR_DOT/LSFT(KC_COMM)/' -e's/FR_SLSH/LSFT(KC_DOT)/' -e's/FR_SECT/LSFT(KC_SLSH)/' -e's/FR_TILD/ALGR(KC_2)/' -e's/FR_HASH/ALGR(KC_3)/' -e's/FR_LCBR/ALGR(KC_4)/' -e's/FR_LBRC/ALGR(KC_5)/' -e's/FR_PIPE/ALGR(KC_6)/' -e's/FR_GRV/ALGR(KC_7)/' -e's/FR_BSLS/ALGR(KC_8)/' -e's/FR_CCIRC/ALGR(KC_9)/' -e's/FR_AT/ALGR(KC_0)/' -e's/FR_RBRC/ALGR(KC_MINS)/' -e's/FR_RCBR/ALGR(KC_EQL)/' -e's/FR_EURO/ALGR(KC_E)/' -e's/FR_BULT/ALGR(KC_RBRC)/' "${LAYOUT_FILE}"
done
rm -rf "${LAYOUT_FILE}.bak"
