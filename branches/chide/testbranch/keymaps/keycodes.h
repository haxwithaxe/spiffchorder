/*************************************************************************
 * keycodes.h - Constants used for general keyboard mapping              *
 * $Id::                                                               $ *
 *************************************************************************
 * SpiffChorder - Spaceman Spiff's Chording Keyboard Experiment          *
 * Copyright (C) 2006-2012  Mikkel Holm Olsen                            *
 *                                                                       *
 * This program is free software: you can redistribute it and/or modify  *
 * it under the terms of the GNU General Public License as published by  *
 * the Free Software Foundation, either version 3 of the License, or     *
 * (at your option) any later version.                                   *
 *                                                                       *
 * This program is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 * GNU General Public License for more details.                          *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *************************************************************************/

#ifndef _KEYCODES_H
#define _KEYCODES_H
#include <avr/pgmspace.h>

#define KEYMAP_USES_MODIFIERS

/* This is the type of the keymap entries */
#ifdef KEYMAP_USES_MODIFIERS
typedef uint16_t keymap_t;
#else
typedef uint8_t keymap_t;
#endif

typedef keymap_t PROGMEM prog_keymap_t;

/*****************************************
 * Possible keycodes in the chord tables *
 *****************************************/
enum keycodes {
/* first part is simply an enumeration of the allowed scan-codes
   used for USB HID devices */
  KEY__=0,              // Unused key-binding
  KEY_errorRollOver,
  KEY_POSTfail,
  KEY_errorUndefined,
  KEY_A,                // 0x04
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,                // 0x10
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_1,
  KEY_2,
  KEY_3,                // 0x20
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_0,                // 0x27
  KEY_enter,            // 0x28
  KEY_esc,              // 0x29
  KEY_bckspc,           // 0x2A  backspace
  KEY_tab,              // 0x2B
  KEY_spc,              // 0x2C  space
  KEY_minus,            // 0x2D  - (and _)
  KEY_equal,            // 0x2E  = (and +)
  KEY_lbr,              // 0x2F  [
  KEY_rbr,              // 0x30  ]
  KEY_bckslsh,          // 0x31  \ (and |)
  KEY_hash,             // 0x32  Non-US # and ~
  KEY_smcol,            // 0x33  ; (and :)
  KEY_ping,             // 0x34  ' and "
  KEY_grave,            // 0x35  Grave accent and tilde
  KEY_comma,            // 0x36  , (and <)
  KEY_dot,              // 0x37  . (and >)
  KEY_slash,            // 0x38  / (and ?)
  KEY_cpslck,           // 0x39  capslock
  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,               // 0x40
  KEY_F8,
  KEY_F9,
  KEY_F10,
  KEY_F11,
  KEY_F12,
  KEY_PrtScr,
  KEY_scrlck,
  KEY_break,
  KEY_ins,
  KEY_home,
  KEY_pgup,
  KEY_del,
  KEY_end,
  KEY_pgdn,
  KEY_rarr,
  KEY_larr,             // 0x50
  KEY_darr,
  KEY_uarr,
  KEY_numlock,
  KEY_KPslash,
  KEY_KPast,
  KEY_KPminus,
  KEY_KPplus,
  KEY_KPenter,
  KEY_KP1,
  KEY_KP2,
  KEY_KP3,
  KEY_KP4,
  KEY_KP5,
  KEY_KP6,
  KEY_KP7,
  KEY_KP8,              // 0x60
  KEY_KP9,
  KEY_KP0,
  KEY_KPcomma,
  KEY_Euro2,

/* The following are not standard USB HID, but are the modifier keys,
   handeled specially in decoding and mapped to the modifier byte in
   the USB report */
  DIV_Mods,
  MOD_LCTRL=DIV_Mods,   // 0x01
  MOD_LSHIFT,           // 0x02
  MOD_LALT,             // 0x04
  MOD_LGUI,             // 0x08
  MOD_RCTRL,            // 0x10
  MOD_RSHIFT,           // 0x20
  MOD_RALT,             // 0x40
  MOD_RGUI,             // 0x80

/* Next comes the mode change codes */
  DIV_Modes,
  MODE_RESET=DIV_Modes, // Reset (Default mode)
  MODE_MRESET,          // Master Reset (unused)
  MODE_NUM,             // Number/symbols mode
  MODE_NUMLCK,          // Number/symbols lock
  MODE_FUNC,            // Function key mode
  MODE_FUNCLCK,         // Function key lock

/* Then a special mode for both num/sym and shift */
  DIV_Multi,
  MULTI_NumShift=DIV_Multi,

/* And finally macros, that generate multiple key presses */
  DIV_Macro,
  MACRO_000=DIV_Macro,  // 000
  MACRO_00,             // 00
  MACRO_quotes,         // "" and left arrow
  MACRO_parens,         // () and left arrow
  DIV_Last
};

enum modifiers {
  FORCE_LCTRL=0x0100,
  FORCE_LSHIFT=0x0200,
  FORCE_LALT=0x0400,
  FORCE_LGUI=0x0800,
  FORCE_RCTRL=0x1000,
  FORCE_RSHIFT=0x2000,
  FORCE_RALT=0x4000,
  FORCE_RGUI=0x8000,
};


/*********************************************************************************
 * Macro strings defined here - lower bits are key-codes, most significant       *
 * bit is converted to shift.                                                    *
 *********************************************************************************/
const unsigned char MStr_000[] PROGMEM = { KEY_0, KEY_0, KEY_0, 0};
const unsigned char MStr_00[] PROGMEM = { KEY_0, KEY_0, 0};
const unsigned char MStr_quotes[] PROGMEM = { 0x80+KEY_ping, 0x80+KEY_ping, KEY_larr, 0};
const unsigned char MStr_parens[] PROGMEM = { 0x80+KEY_9, 0x80+KEY_0, KEY_larr, 0};

/************************************************************************************
 * Array of the macro strings. Order must be the same as in the keycodes enum       *
 ************************************************************************************/
const unsigned char *macro_strings[DIV_Last-DIV_Macro] PROGMEM = {
  MStr_000,
  MStr_00,
  MStr_quotes,
  MStr_parens,
};

#endif
