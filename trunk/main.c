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

#if defined (__AVR_AT90USB1286__)
# define TEENSYUSB
# include "usb_keyboard.h"
#else
# include "usbdrv.h"
# define DEBUG_LEVEL 0
# include "oddebug.h"
#endif

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
 *
 * USB Connector:
 * -------------
 *  1 (red)    +5V
 *  2 (white)  DATA-
 *  3 (green)  DATA+
 *  4 (black)  GND
 *    
 *                                     VCC
 *                  +--[4k7]--+--[2k2]--+
 *      USB        GND        |                     ATmega-8
 *                            |
 *      (D-)-------+----------+--------[82r]------- PD0
 *                 |
 *      (D+)-------|-----+-------------[82r]------- PD2/INT0
 *                 |     |
 *                 _     _
 *                 ^     ^  2 x 3.6V 
 *                 |     |  zener to GND
 *                 |     |
 *                GND   GND
 */

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


#ifndef TEENSYUSB
/* USB report descriptor (length is defined in usbconfig.h)
   This has been changed to conform to the USB keyboard boot
   protocol */
char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] 
  PROGMEM = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,                    //   REPORT_COUNT (5)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x03,                    //   REPORT_SIZE (3)
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0                           // END_COLLECTION  
};
#endif

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
  PORTB = 0x3F;   /* Enable pull-ups */
  DDRB  = 0x00;   /* Port B are switch inputs */

  PORTC = 0x3F;   /* LEDs on PC0..PC2, switches on PC3..PC5 */
  DDRC  = 0x07;   /* PC0..PC2 are outputs, PC3..PC5 are inputs */
#ifndef TEENSYUSB  
  /* Activate pull-ups except on USB lines */
  PORTD = ~((1 << USB_CFG_DMINUS_BIT) | (1 << USB_CFG_DPLUS_BIT));
  DDRD  = 0x02;   /* UART TX is output */  

  usbDeviceDisconnect(); /* Do a proper USB reset */
  uint8_t i=0;
  while (--i) {
    wdt_reset();
    _delay_ms(1);
  }
  usbDeviceConnect();
#endif
  PORTC = 0x38;   /* Turn off LEDs */

#if defined (__AVR_ATmega168__)
# define TIFR_REG TIFR0 
# define CMA_VECT TIMER2_COMPA_vect
  /* configure timer 0 for a rate of 12M/(1024 * 256) = 45.78 Hz (~22ms) */
  TCCR0A = 0;     /* Normal Mode, OC disabled */
  TCCR0B = 5;     /* timer 0 prescaler: 1024 */
  /* configure timer 2 for a rate of 12M/(256 * 47) = 997.3 Hz (~1ms) */
  OCR2A = (uint8_t)((double)F_CPU/256/1000+0.5);
  TCCR2A = (1<<WGM21); /* CTC-mode */
  TCCR2B = (6<<CS20);  /* prescaler=256 */
  TIMSK2|=(1<<OCIE2A);  /* Enable compare match interrupt */
#elif defined (__AVR_ATmega8__)
# define TIFR_REG TIFR
# define CMA_VECT TIMER2_COMP_vect
  /* configure timer 0 for a rate of 12M/(1024 * 256) = 45.78 Hz (~22ms) */
  TCCR0 = 5;           /* timer 0 prescaler: 1024 */
  /* configure timer 2 for a rate of 12M/(256 * 47) = 997.3 Hz (~1ms) */
  OCR2 = (uint8_t)((double)F_CPU/256/1000+0.5);
  TCCR2 = (1<<WGM21)|(6<<CS20); /* CTC-mode, prescaler=256 */
  TIMSK|=(1<<OCIE2);   /* Enable compare match interrupt */
#elif defined (__AVR_AT90USB1286__)
# define TIFR_REG TIFR0
  TCCR0A = 0x00;
  TCCR0B = 0x05;
  TIMSK2|=(1<<OCIE2A); /* Enable compare match interrupt */
  //TIMSK0 = (1<<TOIE0); // from teensy specific code
#else
#error Selected microcontroller not supported
#endif

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


/* Scan the keys, debounce, and report changes in state */
uint8_t scankeys(void) {
  static uint8_t olddata=0xFF;
  uint8_t retval=0;
  uint8_t data;

  data=(PINB&0x3F)|(PIND&0xC0); // Read keys
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

#ifndef TEENSYUSB
uint8_t usbFunctionSetup(uint8_t data[8]) {
  usbRequest_t *rq = (void *)data;
  usbMsgPtr = reportBuffer;
  if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
    if(rq->bRequest == USBRQ_HID_GET_REPORT){  
      /* wValue: ReportType (highbyte), ReportID (lowbyte) */
      /* we only have one report type, so don't look at wValue */
      return sizeof(reportBuffer);
    }else if(rq->bRequest == USBRQ_HID_SET_REPORT){
      if (rq->wLength.word == 1) { /* We expect one byte reports */
        expectReport=1;
        return 0xFF; /* Call usbFunctionWrite with data */
      }  
    }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
      usbMsgPtr = &idleRate;
      return 1;
    }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
      idleRate = rq->wValue.bytes[1];
    }else if(rq->bRequest == USBRQ_HID_GET_PROTOCOL) {
      if (rq->wValue.bytes[1] < 1) {
        protocolVer = rq->wValue.bytes[1];
      }
    }else if(rq->bRequest == USBRQ_HID_SET_PROTOCOL) {
      usbMsgPtr = &protocolVer;
      return 1;
    }
  }
  return 0;
}


/* The write function is called when LEDs should be set */
uint8_t usbFunctionWrite(uint8_t *data, uint8_t len) {
  if ((expectReport)&&(len==1)) {
    LEDstate=data[0]; /* Get the state of all 5 LEDs */
  }
  expectReport=0;
  return 0x01;
}
#endif
int main(void) {
  uint8_t updateNeeded = 0;
  uint8_t idleCounter = 0;

  wdt_enable(WDTO_2S); /* Enable watchdog timer 2s */
  hardwareInit(); /* Initialize hardware (I/O) */

#ifdef TEENSYUSB
  usb_init();
  while (!usb_configured()) /* wait */ ;
  _delay_ms(1000);
#else
  odDebugInit();
  usbInit(); /* Initialize USB stack processing */
  sei(); /* Enable global interrupts */
#endif
  
  for(;;){  /* Main loop */
    wdt_reset(); /* Reset the watchdog */
    usbPoll(); /* Poll the USB stack */
    
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
    if (updateNeeded && usbInterruptIsReady()) {
      updateNeeded = 0;
#ifdef TEENSYUSB
		for (int z = 2;z<=9;z++)
		{
			keyboard_keys[z-2]=reportBuffer[z];
		}
		usb_keyboard_press(reportBuffer[2],reportBuffer[0]);
#else
      usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
#endif
    }
  }
  return 0;
}
