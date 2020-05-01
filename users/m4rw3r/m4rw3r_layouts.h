#ifndef M4RW3R_LAYOUTS_H
#define M4RW3R_LAYOUTS_H

#include "m4rw3r.h"

// TODO: What to put on the brightness key?
// TODO: Use a mouse-key instead of caps for push to talk?
// TODO: Make sure it matches planck too

/**
 * Modifications vs the default Preonic/Planck layouts:
 * 
 * - Moved Ctrl GUI Alt cluster one key to the left
 * - Swapped GUI and Alt to mimic standard Windows keyboard
 * - Raise/lower no longer change BKSP to DEL
 * - Lower + arrows = Home, pgdn, pgup, end
 * - Drop Colemak and Dvorak
 * - ADJUST HJKL are arrows
 */

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CtlEsc|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  | Alt  |Hyper |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 * 
 * On MAC the last row is swapped to:
 * 
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |Hyper | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 * 
 * Use the KC_MAC keycode to set the OS to MAC.
 */

#define M_TRANSPA     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______

#define M_BASE_R1  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL
#define M_BASE_R2  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC
#define M_BASE_R3  CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define M_BASE_R4  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT

// Last row with modifiers for ortho
#define M_BASE_R5     KC_LCTL, KC_LGUI, KC_LALT, KC_F13,  LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#define M_MAC_R5      KC_LCTL, KC_F13,  KC_LALT, KC_LGUI, LOWER,   _______, _______, _______, _______, _______, _______, _______
#define M_GAME_R5     _______, _______, _______, _______, G_LOWER, _______, _______, _______, _______, _______, _______, _______

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | PScr |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
// We split LOWER into two parts since the _GAME_LOWER layer will use the right side of the lower layer as is
#define M_LOWER_R2_L    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define M_LOWER_R3_L    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define M_LOWER_R4_L    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11
#define M_LOWER_R5_L    _______, _______, _______, _______, _______, _______

#define M_LOWER_R2_R(b) KC_CIRC, KC_AMPR, KC_ASTR,   KC_LPRN, KC_RPRN, b
#define M_LOWER_R3_R    KC_F6,   KC_UNDS, KC_PLUS,   KC_LCBR, KC_RCBR, KC_PIPE
#define M_LOWER_R4_R    KC_F12,S(KC_NUHS),S(KC_NUBS),KC_PSCR, _______, _______
#define M_LOWER_R5_R    _______, _______, KC_MNXT,   KC_VOLD, KC_VOLU, KC_MPLY

#define M_LOWER_R2 M_LOWER_R2_L, M_LOWER_R2_R(_______)
#define M_LOWER_R3 M_LOWER_R3_L, M_LOWER_R3_R
#define M_LOWER_R4 M_LOWER_R4_L, M_LOWER_R4_R
#define M_LOWER_R5 M_LOWER_R5_L, M_LOWER_R5_R
#define M_LOWER_R1 M_LOWER_R2

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   Å  |   Ä  |   Ö  |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |   €  |      |      |      |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
#define M_RAISE_R1 M_RAISE_R2
#define M_RAISE_R2 KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL
#define M_RAISE_R3 _______, KX_AA,   KX_AE,   KX_OE,   _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS
#define M_RAISE_R4 _______, _______, _______, KX_EURO, _______, _______, _______, KC_NUHS, KC_NUBS, _______, _______, _______
#define M_RAISE_R5 _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END

// TODO: Update media on Planck/Preonic
/**
 * Standard keyboard-agnostic ADJUST layer row for QWERTY and bottom row for ortho
 *
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Reset| Debug|EEPRES|OS:Lnx|OS:Win|OS:Mac|      |      |TermOf|TermOn| Del  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | LEFT | DOWN |  UP  |RIGHT |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |MPrev | Vol- | Vol+ |MNext |      |Play  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev |Brite-|Brite+|      |
 * `-----------------------------------------------------------------------------------'
 */
#define M_ADJUST_R2 _______, RESET,   DEBUG,   EEP_RST, KC_LNX,  KC_WIN,  KC_MAC,  _______, _______,TERM_OFF, TERM_ON, KC_DEL
#define M_ADJUST_R5 _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_BRID, KC_BRIU, _______

#endif