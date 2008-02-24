/*********************************************************************
 * keycodes.h - Constants used for general keyboard mapping          *
 * $Id::                                                           $ *
 *********************************************************************
 * SpiffChorder is Copyright (C) 2006-2008 Mikkel Holm Olsen         *
 * based on HID-Test by Christian Starkjohann, Objective Development *
 *********************************************************************
 * Spaceman Spiff's Chording Keyboard Experiment (SpiffChorder for   *
 * short) is free software; you can redistribute it and/or modify    *
 * it under the terms of the OBDEV license, as found in the          *
 * licence.txt file.                                                 *
 *                                                                   *
 * SpiffChorder is distributed in the hope that it will be useful,   *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the     *
 * OBDEV license for further details.                                *
 *********************************************************************/

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
/* And finally special keys that do not generate normal keypresses */
  DIV_Special,
  SPC_000=DIV_Special,  // 000
  SPC_00,               // 00
  SPC_quotes,           // "" and left arrow
//  SPC_dollar,           // $
//  SPC_percent,          // %
//  SPC_ampersand,        // &
//  SPC_question,         // ?
  SPC_parens,           // () and left arrow
//  SPC_ast,              // * (Shift-8)
//  SPC_plus,             // + (Shift-=)
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
 * Special key strings defined here - lower bits are key-codes, most significant *
 * bit is converted to shift.                                                    *
 *********************************************************************************/
const unsigned char SpStr_000[] PROGMEM = { KEY_0, KEY_0, KEY_0, 0};
const unsigned char SpStr_00[] PROGMEM = { KEY_0, KEY_0, 0};
const unsigned char SpStr_quotes[] PROGMEM = { 0x80+KEY_ping, 0x80+KEY_ping, KEY_larr, 0};
//const unsigned char SpStr_dollar[] PROGMEM = { 0x80+KEY_4, 0};
//const unsigned char SpStr_percent[] PROGMEM = { 0x80+KEY_5, 0};
//const unsigned char SpStr_ampersand[] PROGMEM = { 0x80+KEY_7, 0};
//const unsigned char SpStr_question[] PROGMEM = { 0x80+KEY_slash, 0};
const unsigned char SpStr_parens[] PROGMEM = { 0x80+KEY_9, 0x80+KEY_0, KEY_larr, 0};
//const unsigned char SpStr_ast[] PROGMEM = { 0x80+KEY_8, 0};
//const unsigned char SpStr_plus[] PROGMEM = { 0x80+KEY_equal, 0};

/************************************************************************************
 * Array of the special key strings. Order must be the same as in the keycodes enum *
 ************************************************************************************/
const unsigned char *special_strings[DIV_Last-DIV_Special] PROGMEM = {
  SpStr_000,
  SpStr_00,
  SpStr_quotes,
//  SpStr_dollar,
//  SpStr_percent,
//  SpStr_ampersand,
//  SpStr_question,
  SpStr_parens,
//  SpStr_ast,
//  SpStr_plus
};


#endif
