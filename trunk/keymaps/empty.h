/*************************************************************************
 * empty.h                                                               *
 * a Blank Keyboard mapping for a 7 key chorder with 3 modes             *
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
 *************************************************************************
 * This empty map was prepared from nasa_us.h by Greg Priest-Dorman      *
 *************************************************************************/
#ifndef KEYMAP_H
#define KEYMAP_H
#include <keycodes.h>
#include <avr/pgmspace.h>

/**********************************************************
 *  order is  Far Thumb, Center Thumb, Near Thumb button  *
 *  Index Finger, Middle Finger, Ring Finger, Pinky       *
 *  FCN IMRP                                              *
 *                                                        *
 * Default mode accessed by MODE_RESET or default state   *
 **********************************************************/
const keymap_t keymap_default[128] PROGMEM = {
  KEY__,          // --- ----  0x00 no keys pressed
  KEY__,          // --- ---P  0x01
  KEY__,          // --- --R-  0x02
  KEY__,          // --- --RP  0x03
  KEY__,          // --- -M--  0x04
  KEY__,          // --- -M-P  0x05
  KEY__,          // --- -MR-  0x06
  KEY__,          // --- -MRP  0x07

  KEY__,          // --- I---  0x08
  KEY__,          // --- I--P  0x09
  KEY__,          // --- I-R-  0x0A
  KEY__,          // --- I-RP  0x0B
  KEY__,          // --- IM--  0x0C
  KEY__,          // --- IM-P  0x0D
  KEY__,          // --- IMR-  0x0E
  KEY__,          // --- IMRP  0x0F

  KEY__,          // --N ----  0x10
  KEY__,          // --N ---P  0x11
  KEY__,          // --N --R-  0x12
  KEY__,          // --N --RP  0x13
  KEY__,          // --N -M--  0x14
  KEY__,          // --N -M-P  0x15
  KEY__,          // --N -MR-  0x16
  KEY__,          // --N -MRP  0x17

  KEY__,          // --N I---  0x18
  KEY__,          // --N I--P  0x19
  KEY__,          // --N I-R-  0x1A
  KEY__,          // --N I-RP  0x1B
  KEY__,          // --N IM--  0x1C
  KEY__,          // --N IM-P  0x1D
  KEY__,          // --N IMR-  0x1E
  KEY__,          // --N IMRP  0x1F

  KEY__,          // -C- ----  0x20
  KEY__,          // -C- ---P  0x21
  KEY__,          // -C- --R-  0x22
  KEY__,          // -C- --RP  0x23
  KEY__,          // -C- -M--  0x24
  KEY__,          // -C- -M-P  0x25
  KEY__,          // -C- -MR-  0x26
  KEY__,          // -C- -MRP  0x27

  KEY__,          // -C- I---  0x28
  KEY__,          // -C- I--P  0x29
  KEY__,          // -C- I-R-  0x2A
  KEY__,          // -C- I-RP  0x2B
  KEY__,          // -C- IM--  0x2C
  KEY__,          // -C- IM-P  0x2D
  KEY__,          // -C- IMR-  0x2E
  KEY__,          // -C- IMRP  0x2F

  KEY__,          // -CN ----  0x30
  KEY__,          // -CN ---P  0x31
  KEY__,          // -CN --R-  0x32
  KEY__,          // -CN --RP  0x33
  KEY__,          // -CN -M--  0x34
  KEY__,          // -CN -M-P  0x35
  KEY__,          // -CN -MR-  0x36
  KEY__,          // -CN -MRP  0x37

  KEY__,          // -CN I---  0x38
  KEY__,          // -CN I--P  0x39
  KEY__,          // -CN I-R-  0x3A
  KEY__,          // -CN I-RP  0x3B
  KEY__,          // -CN IM--  0x3C
  KEY__,          // -CN IM-P  0x3D
  KEY__,          // -CN IMR-  0x3E
  KEY__,          // -CN IMRP  0x3F

  KEY__,          // F-- ----  0x40
  KEY__,          // F-- ---P  0x41
  KEY__,          // F-- --R-  0x42
  KEY__,          // F-- --RP  0x43
  KEY__,          // F-- -M--  0x44
  KEY__,          // F-- -M-P  0x45
  KEY__,          // F-- -MR-  0x46
  KEY__,          // F-- -MRP  0x47

  KEY__,          // F-- I---  0x48
  KEY__,          // F-- I--P  0x49
  KEY__,          // F-- I-R-  0x4A
  KEY__,          // F-- I-RP  0x4B
  KEY__,          // F-- IM--  0x4C
  KEY__,          // F-- IM-P  0x4D
  KEY__,          // F-- IMR-  0x4E
  KEY__,          // F-- IMRP  0x4F

  KEY__,          // F-N ----  0x50
  KEY__,          // F-N ---P  0x51
  KEY__,          // F-N --R-  0x52
  KEY__,          // F-N --RP  0x53
  KEY__,          // F-N -M--  0x54
  KEY__,          // F-N -M-P  0x55
  KEY__,          // F-N -MR-  0x56
  KEY__,          // F-N -MRP  0x57

  KEY__,          // F-N I---  0x58
  KEY__,          // F-N I--P  0x59
  KEY__,          // F-N I-R-  0x5A
  KEY__,          // F-N I-RP  0x5B
  KEY__,          // F-N IM--  0x5C
  KEY__,          // F-N IM-P  0x5D
  KEY__,          // F-N IMR-  0x5E
  KEY__,          // F-N IMRP  0x5F

  KEY__,          // FC- ----  0x60
  KEY__,          // FC- ---P  0x61
  KEY__,          // FC- --R-  0x62
  KEY__,          // FC- --RP  0x63
  KEY__,          // FC- -M--  0x64
  KEY__,          // FC- -M-P  0x65
  KEY__,          // FC- -MR-  0x66
  KEY__,          // FC- -MRP  0x67

  KEY__,          // FC- I---  0x68
  KEY__,          // FC- I--P  0x69
  KEY__,          // FC- I-R-  0x6A
  KEY__,          // FC- I-RP  0x6B
  KEY__,          // FC- IM--  0x6C
  KEY__,          // FC- IM-P  0x6D
  KEY__,          // FC- IMR-  0x6E
  KEY__,          // FC- IMRP  0x6F

  KEY__,          // FCN ----  0x70
  KEY__,          // FCN ---P  0x71
  KEY__,          // FCN --R-  0x72
  KEY__,          // FCN --RP  0x73
  KEY__,          // FCN -M--  0x74
  KEY__,          // FCN -M-P  0x75
  KEY__,          // FCN -MR-  0x76
  KEY__,          // FCN -MRP  0x77

  KEY__,          // FCN I---  0x78
  KEY__,          // FCN I--P  0x79
  KEY__,          // FCN I-R-  0x7A
  KEY__,          // FCN I-RP  0x7B
  KEY__,          // FCN IM--  0x7C
  KEY__,          // FCN IM-P  0x7D
  KEY__,          // FCN IMR-  0x7E
  KEY__           // FCN IMRP  0x7F
};

/*****************************************
 * 2nd mode default name is NUM          *
 * accessed by MODE_NUM and MODE_NUMLCK  *
 *****************************************/
const keymap_t keymap_numsym[128] PROGMEM = {
  KEY__,          // --- ----  0x00
  KEY__,          // --- ---P  0x01
  KEY__,          // --- --R-  0x02
  KEY__,          // --- --RP  0x03
  KEY__,          // --- -M--  0x04
  KEY__,          // --- -M-P  0x05
  KEY__,          // --- -MR-  0x06
  KEY__,          // --- -MRP  0x07

  KEY__,          // --- I---  0x08
  KEY__,          // --- I--P  0x09
  KEY__,          // --- I-R-  0x0A
  KEY__,          // --- I-RP  0x0B
  KEY__,          // --- IM--  0x0C
  KEY__,          // --- IM-P  0x0D
  KEY__,          // --- IMR-  0x0E
  KEY__,          // --- IMRP  0x0F

  KEY__,          // --N ----  0x10
  KEY__,          // --N ---P  0x11
  KEY__,          // --N --R-  0x12
  KEY__,          // --N --RP  0x13
  KEY__,          // --N -M--  0x14
  KEY__,          // --N -M-P  0x15
  KEY__,          // --N -MR-  0x16
  KEY__,          // --N -MRP  0x17

  KEY__,          // --N I---  0x18
  KEY__,          // --N I--P  0x19
  KEY__,          // --N I-R-  0x1A
  KEY__,          // --N I-RP  0x1B
  KEY__,          // --N IM--  0x1C
  KEY__,          // --N IM-P  0x1D
  KEY__,          // --N IMR-  0x1E
  KEY__,          // --N IMRP  0x1F

  KEY__,          // -C- ----  0x20
  KEY__,          // -C- ---P  0x21
  KEY__,          // -C- --R-  0x22
  KEY__,          // -C- --RP  0x23
  KEY__,          // -C- -M--  0x24
  KEY__,          // -C- -M-P  0x25
  KEY__,          // -C- -MR-  0x26
  KEY__,          // -C- -MRP  0x27

  KEY__,          // -C- I---  0x28
  KEY__,          // -C- I--P  0x29
  KEY__,          // -C- I-R-  0x2A
  KEY__,          // -C- I-RP  0x2B
  KEY__,          // -C- IM--  0x2C
  KEY__,          // -C- IM-P  0x2D
  KEY__,          // -C- IMR-  0x2E
  KEY__,          // -C- IMRP  0x2F

  KEY__,          // -CN ----  0x30
  KEY__,          // -CN ---P  0x31
  KEY__,          // -CN --R-  0x32
  KEY__,          // -CN --RP  0x33
  KEY__,          // -CN -M--  0x34
  KEY__,          // -CN -M-P  0x35
  KEY__,          // -CN -MR-  0x36
  KEY__,          // -CN -MRP  0x37

  KEY__,          // -CN I---  0x38
  KEY__,          // -CN I--P  0x39
  KEY__,          // -CN I-R-  0x3A
  KEY__,          // -CN I-RP  0x3B
  KEY__,          // -CN IM--  0x3C
  KEY__,          // -CN IM-P  0x3D
  KEY__,          // -CN IMR-  0x3E
  KEY__,          // -CN IMRP  0x3F

  KEY__,          // F-- ----  0x40
  KEY__,          // F-- ---P  0x41
  KEY__,          // F-- --R-  0x42
  KEY__,          // F-- --RP  0x43
  KEY__,          // F-- -M--  0x44
  KEY__,          // F-- -M-P  0x45
  KEY__,          // F-- -MR-  0x46
  KEY__,          // F-- -MRP  0x47

  KEY__,          // F-- I---  0x48
  KEY__,          // F-- I--P  0x49
  KEY__,          // F-- I-R-  0x4A
  KEY__,          // F-- I-RP  0x4B
  KEY__,          // F-- IM--  0x4C
  KEY__,          // F-- IM-P  0x4D
  KEY__,          // F-- IMR-  0x4E
  KEY__,          // F-- IMRP  0x4F

  KEY__,          // F-N ----  0x50
  KEY__,          // F-N ---P  0x51
  KEY__,          // F-N --R-  0x52
  KEY__,          // F-N --RP  0x53
  KEY__,          // F-N -M--  0x54
  KEY__,          // F-N -M-P  0x55
  KEY__,          // F-N -MR-  0x56
  KEY__,          // F-N -MRP  0x57

  KEY__,          // F-N I---  0x58
  KEY__,          // F-N I--P  0x59
  KEY__,          // F-N I-R-  0x5A
  KEY__,          // F-N I-RP  0x5B
  KEY__,          // F-N IM--  0x5C
  KEY__,          // F-N IM-P  0x5D
  KEY__,          // F-N IMR-  0x5E
  KEY__,          // F-N IMRP  0x5F

  KEY__,          // FC- ----  0x60
  KEY__,          // FC- ---P  0x61
  KEY__,          // FC- --R-  0x62
  KEY__,          // FC- --RP  0x63
  KEY__,          // FC- -M--  0x64
  KEY__,          // FC- -M-P  0x65
  KEY__,          // FC- -MR-  0x66
  KEY__,          // FC- -MRP  0x67

  KEY__,          // FC- I---  0x68
  KEY__,          // FC- I--P  0x69
  KEY__,          // FC- I-R-  0x6A
  KEY__,          // FC- I-RP  0x6B
  KEY__,          // FC- IM--  0x6C
  KEY__,          // FC- IM-P  0x6D
  KEY__,          // FC- IMR-  0x6E
  KEY__,          // FC- IMRP  0x6F

  KEY__,          // FCN ----  0x70
  KEY__,          // FCN ---P  0x71
  KEY__,          // FCN --R-  0x72
  KEY__,          // FCN --RP  0x73
  KEY__,          // FCN -M--  0x74
  KEY__,          // FCN -M-P  0x75
  KEY__,          // FCN -MR-  0x76
  KEY__,          // FCN -MRP  0x77

  KEY__,          // FCN I---  0x78
  KEY__,          // FCN I--P  0x79
  KEY__,          // FCN I-R-  0x7A
  KEY__,          // FCN I-RP  0x7B
  KEY__,          // FCN IM--  0x7C
  KEY__,          // FCN IM-P  0x7D
  KEY__,          // FCN IMR-  0x7E
  KEY__           // FCN IMRP  0x7F
};


/******************************************
 * 3nd mode default name is FUNC          *
 * accessed by MODE_FUNC and MODE_FUNCLCK *
 ******************************************/

const keymap_t keymap_function[128] PROGMEM = {
  KEY__,          // --- ----  0x00
  KEY__,          // --- ---P  0x01
  KEY__,          // --- --R-  0x02
  KEY__,          // --- --RP  0x03
  KEY__,          // --- -M--  0x04
  KEY__,          // --- -M-P  0x05
  KEY__,          // --- -MR-  0x06
  KEY__,          // --- -MRP  0x07

  KEY__,          // --- I---  0x08
  KEY__,          // --- I--P  0x09
  KEY__,          // --- I-R-  0x0A
  KEY__,          // --- I-RP  0x0B
  KEY__,          // --- IM--  0x0C
  KEY__,          // --- IM-P  0x0D
  KEY__,          // --- IMR-  0x0E
  KEY__,          // --- IMRP  0x0F

  KEY__,          // --N ----  0x10
  KEY__,          // --N ---P  0x11
  KEY__,          // --N --R-  0x12
  KEY__,          // --N --RP  0x13
  KEY__,          // --N -M--  0x14
  KEY__,          // --N -M-P  0x15
  KEY__,          // --N -MR-  0x16
  KEY__,          // --N -MRP  0x17

  KEY__,          // --N I---  0x18
  KEY__,          // --N I--P  0x19
  KEY__,          // --N I-R-  0x1A
  KEY__,          // --N I-RP  0x1B
  KEY__,          // --N IM--  0x1C
  KEY__,          // --N IM-P  0x1D
  KEY__,          // --N IMR-  0x1E
  KEY__,          // --N IMRP  0x1F

  KEY__,          // -C- ----  0x20
  KEY__,          // -C- ---P  0x21
  KEY__,          // -C- --R-  0x22
  KEY__,          // -C- --RP  0x23
  KEY__,          // -C- -M--  0x24
  KEY__,          // -C- -M-P  0x25
  KEY__,          // -C- -MR-  0x26
  KEY__,          // -C- -MRP  0x27

  KEY__,          // -C- I---  0x28
  KEY__,          // -C- I--P  0x29
  KEY__,          // -C- I-R-  0x2A
  KEY__,          // -C- I-RP  0x2B
  KEY__,          // -C- IM--  0x2C
  KEY__,          // -C- IM-P  0x2D
  KEY__,          // -C- IMR-  0x2E
  KEY__,          // -C- IMRP  0x2F

  KEY__,          // -CN ----  0x30
  KEY__,          // -CN ---P  0x31
  KEY__,          // -CN --R-  0x32
  KEY__,          // -CN --RP  0x33
  KEY__,          // -CN -M--  0x34
  KEY__,          // -CN -M-P  0x35
  KEY__,          // -CN -MR-  0x36
  KEY__,          // -CN -MRP  0x37

  KEY__,          // -CN I---  0x38
  KEY__,          // -CN I--P  0x39
  KEY__,          // -CN I-R-  0x3A
  KEY__,          // -CN I-RP  0x3B
  KEY__,          // -CN IM--  0x3C
  KEY__,          // -CN IM-P  0x3D
  KEY__,          // -CN IMR-  0x3E
  KEY__,          // -CN IMRP  0x3F

  KEY__,          // F-- ----  0x40
  KEY__,          // F-- ---P  0x41
  KEY__,          // F-- --R-  0x42
  KEY__,          // F-- --RP  0x43
  KEY__,          // F-- -M--  0x44
  KEY__,          // F-- -M-P  0x45
  KEY__,          // F-- -MR-  0x46
  KEY__,          // F-- -MRP  0x47

  KEY__,          // F-- I---  0x48
  KEY__,          // F-- I--P  0x49
  KEY__,          // F-- I-R-  0x4A
  KEY__,          // F-- I-RP  0x4B
  KEY__,          // F-- IM--  0x4C
  KEY__,          // F-- IM-P  0x4D
  KEY__,          // F-- IMR-  0x4E
  KEY__,          // F-- IMRP  0x4F

  KEY__,          // F-N ----  0x50
  KEY__,          // F-N ---P  0x51
  KEY__,          // F-N --R-  0x52
  KEY__,          // F-N --RP  0x53
  KEY__,          // F-N -M--  0x54
  KEY__,          // F-N -M-P  0x55
  KEY__,          // F-N -MR-  0x56
  KEY__,          // F-N -MRP  0x57

  KEY__,          // F-N I---  0x58
  KEY__,          // F-N I--P  0x59
  KEY__,          // F-N I-R-  0x5A
  KEY__,          // F-N I-RP  0x5B
  KEY__,          // F-N IM--  0x5C
  KEY__,          // F-N IM-P  0x5D
  KEY__,          // F-N IMR-  0x5E
  KEY__,          // F-N IMRP  0x5F

  KEY__,          // FC-  ---  0x60
  KEY__,          // FC- ---P  0x61
  KEY__,          // FC- --R-  0x62
  KEY__,          // FC- --RP  0x63
  KEY__,          // FC- -M--  0x64
  KEY__,          // FC- -M-P  0x65
  KEY__,          // FC- -MR-  0x66
  KEY__,          // FC- -MRP  0x67

  KEY__,          // FC- I---  0x68
  KEY__,          // FC- I--P  0x69
  KEY__,          // FC- I-R-  0x6A
  KEY__,          // FC- I-RP  0x6B
  KEY__,          // FC- IM--  0x6C
  KEY__,          // FC- IM-P  0x6D
  KEY__,          // FC- IMR-  0x6E
  KEY__,          // FC- IMRP  0x6F

  KEY__,          // FCN ----  0x70
  KEY__,          // FCN ---P  0x71
  KEY__,          // FCN --R-  0x72
  KEY__,          // FCN --RP  0x73
  KEY__,          // FCN -M--  0x74
  KEY__,          // FCN -M-P  0x75
  KEY__,          // FCN -MR-  0x76
  KEY__,          // FCN -MRP  0x77

  KEY__,          // FCN I---  0x78
  KEY__,          // FCN I--P  0x79
  KEY__,          // FCN I-R-  0x7A
  KEY__,          // FCN I-RP  0x7B
  KEY__,          // FCN IM--  0x7C
  KEY__,          // FCN IM-P  0x7D
  KEY__,          // FCN IMR-  0x7E
  KEY__           // FCN IMRP  0x7F
};

#endif

