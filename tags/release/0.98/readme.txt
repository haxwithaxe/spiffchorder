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
with the USB port. Additionally, a number of keys are connected for the
chorder. For the current configuration, 7 keys are used, but for future
expansion an eigth input-line has been allocated for the normal chord
decoding, as well as 3 lines that will be mapped directly to keys or
functions (e.g. modifier keys or mouse-clicks for a pointing device).
Optionally 3 LEDs can be connected, intended to show the internal
state/mode of the SpiffChorder.


Legacy hardware
---------------

Because the original design of the SpiffChorder was based on ATmega8
instead of ATmega168, some builders have hardware platforms based on
ATmega8. For this reason it has been decided to try and keep compability
with the old ATmega8 design, with the limitations presented by the
smaller amount of flash memory for program storage. If you are 
constructing the SpiffChorder, use of the ATmega8 is discouraged, because
of code size constraints. One of the nice properties of the SpiffChorder
design is ability to use a USB bootloader, allowing the SpiffChorder
firmware to be updated over the existing USB connection. The bootloader
uses a 2kB bootblock, which leaves only 6kB for code on the ATmega8,
versus 14kB on the ATmega168. At the current stage the code for the
SpiffChorder is very close to the 6kB limit, so just getting a few of 
the planned additional features implemented will likely pass the boundary,
meaning that people with ATmega8-based hardware cannot use the bootloader.

Also, there are plans to extend the SpiffChorder into a composite device,
implementing both a (chording) keyboard and a pointing device, such as the
mini trackball from SparkFun:
http://www.sparkfun.com/commerce/product_info.php?products_id=755

With this addition the code will very likely be larger, even above the
8kB limit, so for this the ATmega168 will probably be the only way to 
go.

If, dispite these warnings, you want to compile the SpiffChorder 
firmware for ATmega8, this should be possible by simply changing the
MCU-line in the Makefile. In the places where hardware differences
influence the code, an attempt has been made to make conditional
code, compiling on the different platforms, based on the MCU selected
in the Makefile.

Since the ATmega8 is not officially supported, especially if changes
are made to the code, pay attention to the size of the code generated.
At the end of the build process you should see a dump of the different
sizes, like the following:
Size after:
main.elf  :
section            size      addr
.text              5904         0
.data                14   8388704
.bss                 76   8388718
.stab              5328         0
....

The number to look for is the size of the .text segment, in this case
5904 bytes. If using the ATmega8, you have 6144 bytes if using a 
bootloader and 8192 bytes otherwise.


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
the device to use an external crystal. The default configuration of the 
AVR device is to use the internal RC oscillator from the factory, but
this is not sufficiently accurate to handle the delicate timing required 
for USB communication. The Makefile has a target called fuses, 
which uses avrdude to set the fuses for the device (provided the avrdude 
settings in the Makefile have been configured in an appropriate way).

If your programmer does not work with avrdude, you should configure the
fuses as follows (hfuse=0xDD,lfuse=0xFF):
  * Boot flash size = 1024 words
  * Brown-out detection level = 2.7 V
  * External crystal 8.0MHz-xxMHz 16K CK/14 CK + 65ms startup
  * Remember to disable the CKDIV8.

I have had problems when setting the BOD-level to 4.3V, resulting in
Windows saying the device was not recogniced, only to properly detect
it a few seconds later. Setting the BOD-level to 2.7V seems to solve
this.

If using the legacy ATmega8 hardware, the fuses should be configured
as follows: Boot Flash size = 1024 words, BOD-level = 4.0V, BOD enabled,
External crystal, 16K CK + 64ms startup (hfuse=0xD9,lfuse=0x3F).

NOTE: The fuse settings shown here do not enable the bootloader, but
starts the SpiffChorder code directly. If a bootloader is used, you
should set the bootloader enable fuse also (which should be described
in the documentation regarding getting the bootloader in place).

Be aware that the firmware provided here does not use OBDEV's USB 
vendor ID, since this originally was not allowed to be used for HID 
devices. Instead a sepearte VID/PID-pair has been acquired for the
SpiffChorder. You may use this PID freely for SpiffChorders, even
when changing the chord mappings or function of the code.


Files
-----
readme.txt              This file.
changes.txt             What has been changed in the different versions.
doc.txt                 Extra documentation (for further development).
license.txt             The license this project is released under.
circuit/                Directory with circuit diagrams in PDF and PNG formats.
usbdrv/                 Directory with the AVR-USB driver and docs.
keymaps/                Keyboard maps (chord maps).
Makefile                Build instructions for GNU Make.
main.c                  Main source code file.
main.hex                Compiled version, ready to be programmed into uC.
usbconfig.h             Configuration for AVR-USB stack.
                        


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
