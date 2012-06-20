/*************************************************************************
 * main.c - Main firmware                                                *
 * Version 0.98                                                          *
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

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <string.h>
#include "usb_keyboard.h"

#define TEENSYUSB
#define KEYPORT PORTC
#define KEYDDR DDRC
#define KEYPIN PINC
#define MODPORT PORTB
#define MODDDR DDRB
#define MODPIN PINB

/* Hardware documentation:
 * ATmega168 (Should also work with ATmega8/ATmega88)
 *
 * PB0     : Pinky key
 * PB1     : Ring finger key
 * PB2     : Middle finger key
 * PB3     : Index finger key
 * PB4     : Near thumb
 * PB5     : Center thumb
 * PB6..PB7: X-tal (12MHz or 16MHz)
 * PC0     : Near LED
 * PC1     : Center LED
 * PC2     : Far LED
 * PC3     : Unused modifier 1
 * PC4     : Unused modifier 2
 * PC5     : Unused modifier 3
 * PD0     : D- USB negative (needs appropriate zener-diode and resistors)
 * PD1     : UART TX
 * PD2/INT0: D+ USB positive (needs appropriate zener-diode and resistors)
 * PD6     : Far thumb
 * PD7     : Extra chord button (unused)
 */
/* AT90USB1286 RELATED */
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

/* Pin definition utils */
#define PIN(p,n) (p & (1 << n))
#define SET_INPUT(ddr) (ddr = 0x00)
#define SET_PULLUP(port) (port = 0xFF)
#define LED_ON(port) (port &= ~(1<<6))
#define LED_OFF(port) (port |= (1<<6))

/* Define Key Pins */
// Pinky key
#define Pinky_R PIN(KEYPIN,0)
// Ring finger key
#define Ring_R PIN(KEYPIN,1)
// Middle finger key
#define Middle_R PIN(KEYPIN,2)
// Index finger key
#define Index_R PIN(KEYPIN,3)
// Near thumb
#define Near_Thumb_R PIN(KEYPIN,4)
// Center thumb
#define Center_Thumb_R PIN(KEYPIN,5)
// Far thumb
#define Far_Thumb_R PIN(KEYPIN,6)

// Unused modifier 1
#define X_mod1 PIN(MODPIN,0)
// Unused modifier 2
#define X_mod2 PIN(MODPIN,1)
// Unused modifier 3
#define X_mod3 PIN(MODPIN,2)
// Extra chord button (unused)
#define XCHRD_R PIN(MODPIN,3)

/* LED PINS */
#define LEDS PORTD
// Near Thumb LED
#define LED_Near_Thumb PORTD
// Center Thumb LED
#define LED_Center_Thumb PORTD
// Far Thumb LED
#define LED_Far_Thumb PORTD

/* Leftovers from original source comments */
// PB6..PB7: X-tal (12MHz or 16MHz)

/* LEDs on a boot-protocol keyboard */
#define LED_NUM     0x01
#define LED_CAPS    0x02
#define LED_SCROLL  0x04
#define LED_COMPOSE 0x08
#define LED_KANA    0x10
uint8_t LEDstate=0;

/* The repeat state and counter in key_repeat can be one of these values
   to signify the state, or it can be higher than REP_STATE_TIMEOUT to
   signify that the timer is running but time-out has not yet occurred */
enum repeat_state_e {
  REP_STATE_READY=0,
  REP_STATE_KEYDOWN_SENT,
  REP_STATE_TIMEOUT
};
/* Key repeat timer/counter. if>REP_STATE_TIMEOUT then decreased by main loop */
volatile uint8_t key_repeat=REP_STATE_READY;

uint8_t repeat_value=REP_STATE_TIMEOUT+
  (int)((double)F_CPU/262144/2+0.5);    // ~ 500ms timeout
uint8_t debounce_value=10;  // 10 ms debounce. Should be loaded from EEPROM.
uint8_t use_early_detect=1; // This is a configuration option

/* Originally used as a mask for the modifier bits, but now also
   used for other x -> 2^x conversions (lookup table). */
const uint8_t modmask[8] PROGMEM = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80
};

/* An array of pointers to the decoding tables */
const prog_keymap_t *keymap_tables[] PROGMEM = {
  keymap_default,                  // The default mode
  keymap_numsym,                   // Numbers/Symbols mode
  keymap_function                  // Function key mode
};

const prog_keymap_t *current_keymap = keymap_default;
const prog_keymap_t *special_keymap = NULL;

/* The ReportBuffer contains the USB report sent to the PC */
static uint8_t reportBuffer[8];    /* buffer for HID reports */
static uint8_t idleRate;           /* in 4 ms units */
static uint8_t protocolVer=1;      /* 0 is the boot protocol, 1 is report protocol */

/* Debounce counter. if>1 then decreased by timer interrupt */
volatile uint8_t debounce=0;

static void hardwareInit(void) {
  SET_PULLUP(MODPORT);   /* Enable pull-ups */
  SET_INPUT(MODDDR);   /* Port B are switch inputs */

  SET_PULLUP(KEYPORT);   /* LEDs on PC0..PC2, switches on PC3..PC5 */
  SET_INPUT(KEYDDR);   /* pins 0-6 are pinky-thumbs keys used to be: PC0..PC2 are outputs, PC3..PC5 are inputs */

#define TIFR_REG TIFR0
  TCCR0A = 0x00;
  TCCR0B = 0x05;
  TIMSK2|=(1<<OCIE2A); // Enable compare match interrupt
  //TIMSK0 = (1<<TOIE0); // from teensy specific code
#ifndef TEENSYUSB
#error Selected microcontroller (__AVR_AT90USB1286__) not supported
#endif
   LED_OFF(LEDS);   /* Turn off LEDs */
}

/* Timer 2 interrupt handler - decrease debounce counter every 1ms */
ISR(CMA_VECT) {
  /* This gets called every 1ms and updates the button debounce counter */
  if (debounce>1) {
    --debounce;
  }
}

/* The modifier keys applied to next keypress and the modifier locks */
uint8_t mod_state=0, mod_lock=0;

/* The current mode and whether to lock the mode or only apply it to one keypress */
uint8_t current_mode=0, lock_mode=0, last_modifiers=0;

/* Used to send the key_up event */
const uint8_t PROGMEM key_up[] = {0};

/* This pointer tells us something needs to be sent before returning to keyboard scanning */
const uint8_t *pendingPtr = key_up;

/* Handle a chord */
unsigned char process_chord(uint8_t chord) {
  uint8_t key;
#ifdef KEYMAP_USES_MODIFIERS
  keymap_t keymods;
  keymods=pgm_read_word(special_keymap?&special_keymap[chord&0x7F]:
                    &current_keymap[chord&0x7F]);
  key=(uint8_t)keymods; /* typecast masks off upper bits */
#else
  key=pgm_read_byte(special_keymap?&special_keymap[chord&0x7F]:
                    &current_keymap[chord&0x7F]);
#endif
  special_keymap=NULL;
  if (key>=DIV_Mods) { // This is not a standard key
    if (key>=DIV_Multi) { // Either Multi-mode or Macro
      if (key>=DIV_Macro) { /* Macro */
        pendingPtr=(const uint8_t*)pgm_read_word(&macro_strings[key-DIV_Macro]);
        mod_state&=mod_lock; 
        if (!lock_mode) { // Reset mode unless it was locked
          current_keymap=keymap_default;
          current_mode=0;
        }
      } else { // Multi
        special_keymap=keymap_numsym; // Numbers/symbols-mode
        mod_state|=0x02; // Left shift
      }
    } else { // Either mods or modes
      if (key>=DIV_Modes) { /* Mode change requested */
        current_mode=(key-DIV_Modes);
        lock_mode=current_mode&0x01;
        current_mode>>=1;
        current_keymap=(const prog_keymap_t*)pgm_read_word(&keymap_tables[current_mode]);
      } else { // Modifier
        mod_state|=pgm_read_byte(&modmask[key-DIV_Mods]);
      }
    }
    key=0;
  }

  if (key) {
    memset(reportBuffer,0,sizeof(reportBuffer)); /* Clear report buffer */
    reportBuffer[2]=key;

#ifdef KEYMAP_USES_MODIFIERS
    key=keymods>>8;
    if (key) {
      reportBuffer[0]=key;
    } else 
#endif
    {
      reportBuffer[0]=mod_state;
    }
    last_modifiers=reportBuffer[0]; /* Save the modifiers for proper clean-up on release */

    mod_state&=mod_lock;
    if (!lock_mode) {
      current_keymap=keymap_default;
      current_mode=0;
    }
    return 1;
  }
  return 0;
}

/* When the state of keys change, handle key-down or key-up */
uint8_t key_change(uint8_t data, uint8_t timeout) {
  static uint8_t latched=0xFF, adding=0;
  uint8_t retval=0;
  if (timeout) {
    // If the same chord has been held for an amount of time - send key-down - repeat starts
    if (adding) retval=process_chord(~latched);
  } else {
    if (latched & ~data) { // buttons(s) pressed
      adding=1;
      latched&=data;
      key_repeat=repeat_value;
    } else if (~latched & data) { // buttons(s) released
      if (use_early_detect?adding:data==0xFF) {
        if (key_repeat!=REP_STATE_KEYDOWN_SENT) retval=process_chord(~latched);
        latched=data;
        adding=0;
      }
      if ((retval)||(key_repeat==REP_STATE_KEYDOWN_SENT)) { // Some key was reported
        if (!pendingPtr) pendingPtr=key_up; // Make sure the key up event is sent immediately
      }
      key_repeat=REP_STATE_READY;
      if (use_early_detect) latched=data;
    }
  }
  return retval;
}

uint8_t read_keys() {
	uint8_t keyvals = KEYPIN;
	return keyvals;
}

/* Scan the keys, debounce, and report changes in state */
uint8_t scankeys(void) {
  static uint8_t olddata=0xFF;
  uint8_t retval=0;
  uint8_t data;

  data=read_keys();
  if (olddata^data) { // Change detected
    if (debounce==0) {
      debounce=debounce_value;
    } else if (debounce==1) {
      retval=key_change(data,0); // Process key change
      olddata=data;
      debounce=0;
    }
  } else {
    if (key_repeat==REP_STATE_TIMEOUT) {
      retval=key_change(data,1); // Send key-down
      key_repeat=REP_STATE_KEYDOWN_SENT;
    }
  }

  return retval;
}

uint8_t getCharFromPending(void) {
  static uint8_t state=0, kval=0;
  memset(reportBuffer,0,sizeof(reportBuffer)); /* Clear report buffer */
  if (state) {
    reportBuffer[0]=last_modifiers;
    state=0;
  } else {
    kval=pgm_read_byte(pendingPtr);
    reportBuffer[0]=(kval&0x80?0x02:0);
    reportBuffer[2]=kval&~0x80;
    if (kval) {
      pendingPtr++;
    } else {
      pendingPtr=NULL;
    }
    state=1;
  }
  return 1;
}

uint8_t expectReport=0;



int main(void) {
  uint8_t updateNeeded = 0;
  uint8_t idleCounter = 0;

  wdt_enable(WDTO_2S); /* Enable watchdog timer 2s */
  hardwareInit(); /* Initialize hardware (I/O) */

  usb_init();
  while (!usb_configured()) /* wait */ ;
  _delay_ms(1000);

  
  for(;;){  /* Main loop */
    wdt_reset(); /* Reset the watchdog */
    //usbPoll(); /* Poll the USB stack */
    
    if (!updateNeeded) {
      if (pendingPtr) {
        updateNeeded=getCharFromPending(); /* Keys pending in output buffer? */
      } else {
        updateNeeded=scankeys(); /* Scan the keyboard for changes */
      }
    }

    /* Check timer if we need periodic reports */
    if (TIFR_REG & (1<<TOV0)) {
      TIFR_REG = 1<<TOV0; /* Reset flag */
      if (key_repeat>REP_STATE_TIMEOUT) {
        --key_repeat;
      }
      if (idleRate != 0) { /* Do we need periodic reports? */
        if(idleCounter > 4){ /* Yes, but not yet */
          idleCounter -= 5;   /* 22 ms/tick */
        } else { /* Yes, it is time now */
          updateNeeded = 1;
          idleCounter = idleRate;
        }
      }
    }
    
    /* If an update is needed, send the report */
    if (updateNeeded) {
      updateNeeded = 0;
		for (int z = 2;z<=9;z++)
		{
			keyboard_keys[z-2]=reportBuffer[z];
		}
		usb_keyboard_press(reportBuffer[2],reportBuffer[0]);
    }
  }
  return 0;
}
