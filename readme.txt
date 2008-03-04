Spaceman Spiff's Chording Keyboard Experiment (SpiffChorder for 
short) is free software; you can redistribute it and/or modify 
it under the terms of the OBDEV license, as found in the 
licence.txt file.
                                                              
SpiffChorder is distributed in the hope that it will be useful,    
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
OBDEV license for further details.
                                                              
Spaceman Spiff's Chording Keyboard Experiment (or SpiffChorder for short)
is an experimental platform for creating a USB chording keyboard. A
chording keyboard or Chorded keyboard is an input device where characters
can be typed by pressing multiple keys at the same time. A popular design 
is the 7-key chorder, where one key is used for each of the index finger, 
middle finger, ring finger and pinky, and 3 keys for the thumb. This can 
be used with either the left or right hand (or a chorder can be used for 
each hand, effectively doubling the typing speed).

For the latest information regarding the SpiffChorder, check the 
project homepage:

  http://symlink.dk/projects/spiffchorder/

and the wiki:

  http://chorder.cs.vassar.edu/spiffchorder/forside

Both the hardware design and software/firmware for the SpiffChorder
is open, and you can make modifications as you see fit. The license is 
based on Objective Development's license, which is now GPL, but with 
the addition that the hardware is documented and open as well.

Objective Development's AVR USB driver is a firmware-only implementation 
of the low speed USB standard (1.5Mbps) which can be used on cheap AVR 
microcontrollers from Atmel.

The hardware for the SpiffChorder is very simple, and consists mainly of 
an ATmega168, a 12MHz crystal, and a few passive components for interfacing 
with the USB port. Apart from this 7 switches are connected, and 
optionally 3 LEDs for indicating the internal state. 


Building the hardware
---------------------

The hardware for SpiffChorder is quite simple. Circuit diagrams are
included in the directory "circuit" in PDF and PNG formats. The USB
interface hardware is based on Mindaugas Milasauskas' MJoy application
(http://www.mindaugas.com/projects/MJoy/). Apart from that, the only
interesting things are the 12MHz crystal and interface to the 7 switches
and optionally 3 LEDs.

No circuit board layout is published, mainly because the application
is so simple that it is easier to realize on a perf-board (strip-board),
but the diagram should provide all needed information to create your own
implementation, whether on a perf-board or with printed circuit boards.

A bill of materials (BOM) can be found in circuit/bom.txt, along with some
additional notes regarding the chosen component values.


Building the firmware
---------------------

The SpiffChorder firmware requires avr-gcc and avr-libc (see 
http://www.nongnu.org/avr-libc/ for more details).

Before attempting to compile, edit the Makefile to select the
desired chord mapping and programmer options.

For the easiest approach, you can use WinAVR under Windows, which is
a bundle of the required libraries and tool-chain packaged for
Windows. It even comes with a good editor (Programmers Notepad),
which was used for the development throughout this project.
WinAVR is available from http://winavr.sourceforge.net/.

After installing WinAVR you should be able to run the command
"make" from the directory where the source code is located, which
will build the firmware. The "Makefile" included with the project is
based on an example from the WinAVR distribution, and has support
for burning the firmware to an AVR device through a range of different
programmers supported by the AVRdude programming utility. With a few
modifications to the Makefile it should be possible to accomplish this
programming by issuing the command "make program". Of course these
commands can also be executed from within Programmers Notepad.

Of course you will need some programming hardware to connect between
the circuit and the PC. Several possibilities exist (and are supported
by AVRdude), including some very simple programmers that can be built
on a tight budget. During the experimentation and development of this
project, I have used an STK500 development board from Atmel. If you 
have the possibility of getting one of these, I can highly recommend it,
not only as a programmer, but for a wealth of experiments that can be
done on the board, before any hardware needs to be built.

It is important that the fuses of the microcontroller are set correctly
before the application will work. The most important thing is to configure
the device to use an external crystal. The AVR device is configured to
use the internal RC oscillator from the factory, but this is not
sufficiently accurate to handle the delicate timing required for USB
communication. Each of the Makefiles have a target called fuses, which
uses avrdude to set the fuses for the device (provided the avrdude 
settings in the Makefile have been configured in an appropriate way).

Be aware that the firmware provided here does not use OBDEV's USB 
vendor ID, since this may not be used for HID devices. Instead a
sepearte VID/PID-pair has been acquired for the SpiffChorder. You may
use this PID freely for SpiffChorders, even when changing the chord
mappings or function of the code.


Files
-----
readme.txt              This file.
changes.txt             What has been changed in the different versions.
license.txt             The license this project is released under.
circuit/                Directory with circuit diagrams in PDF and PNG formats.
usbdrv/                 Directory with the AVR-USB driver and docs.
keymaps/                Keyboard maps (chord maps).
Makefile                Build instructions for GNU Make.
main.c                  Main source code file.
main.hex                Compiled version, ready to be programmed into uC.
                        


License information
-------------------

The SpiffChorder project is based on Objective Development's HIDkeys demo 
application, and although the restriction is mainly that any derivative
works should be published under an Open Source license, the additional
requirements by OBDEV are very resonable, and the entire project has
been released under this license. In other words you should feel free
to use the firmware here for any purpose, but any enhancements should
be given back to the community, in the form of a contribution to OBDEV's
project pages, with full documentation.

See the file license.txt for details.


Copyright
---------

The SpiffChorder project and documentation is Copyright (C) 2006-2008
by Mikkel Holm Olsen (AKA Spaceman Spiff). More information about the
project can be found on http://symlink.dk/projects/spiffchorder/.

$Id$
