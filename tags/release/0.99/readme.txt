SpiffChorder - Spaceman Spiff's Chording Keyboard Experiment
Copyright (C) 2006-2012  Mikkel Holm Olsen

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


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
is open, and you can make modifications as you see fit. Both the hardware
design and the source code for the software/firmware and driver are
released under the terms of the GNU GPL v3.

Objective Development's V-USB driver (Previously AVR-USB) is a firmware-only 
implementation of the low speed USB standard (1.5Mbps) which can be used on 
cheap AVR microcontrollers from Atmel.

The hardware for the SpiffChorder is very simple, and consists mainly of 
an ATmega168, a crystal, and a few passive components for interfacing 
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
bootloader and 8192 bytes otherwise. Remember that the compiler version
also has some influence on this. Older compilers generate smaller code
under many circumstances.


Building the hardware
---------------------

The hardware for SpiffChorder is quite simple. Circuit diagrams are
included in the directory "circuit" in PDF and PNG formats. The USB
interface hardware is based on Mindaugas Milasauskas' MJoy application
(http://www.mindaugas.com/projects/MJoy/). Apart from that, the only
interesting things are the crystal and interface to the 7 switches
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

You may want to try the spiffchorder.hex file first (but this
requires compatible hardware, most notably a 12MHz crystal and
the USB connections on PD0 and PD2). If this works, you can
play around with the code and compile yourself.

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
fuses as follows (efuse=0x01,hfuse=0xD5,lfuse=0xFF on ATmega168 with
avrdude):
  * Boot flash size = 1024 words
  * Preserve EEPROM memory through the chip erase cycle
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
should set the bootloader enable fuse also.

Be aware that the firmware provided here does not use OBDEV's USB 
vendor ID, since this originally was not allowed to be used for HID 
devices. Instead a sepearte VID/PID-pair has been acquired for the
SpiffChorder. You may use this PID freely for SpiffChorders, even
when changing the chord mappings or function of the code.


Boot loader
-----------

In order to let people play with the SpiffChorder code, even if they
do not have regular access to an AVR programming device, a boot 
loader can be used, which will receive the new SpiffChorder firmware
through the USB connection already present.

Of course the boot loader needs to be installed in the chip before
it can be programmed over USB. If you do not have an AVR programmer,
try to find someone who does, and who can help you put the boot loader
in. Alternatively there are several simple programmers that can be
built on a shoestring budget. A range of these are supported by
avrdude, which is included with the WinAVR package, but also available
on Linux and Mac. Check the avrdude documentation or do a search for
"AVR programmer" on Google.

After programming the boot loader into the chip, you need to set the 
fuses correctly, in order for the boot loader to start 
(efuse=0x00,hfuse=0xD5,lfuse=0xFF on ATmega168 with avrdude):
  * Boot flash size = 1024 words
  * Boot reset vector enabled
  * Preserve EEPROM memory through the chip erase cycle
  * Brown-out detection level = 2.7 V
  * External crystal 8.0MHz-xxMHz 16K CK/14 CK + 65ms startup
  * Remember to disable the CKDIV8.

When the fuses are set correctly, it is a good idea to set the boot 
loader protection lock bits for "Boot loader protection mode 3: LPM 
and SPM prohibited in Boot Loader section". This prevents the boot 
loader from erasing itself in case something goes wrong. The other 
lock bits should be left alone.

You can now activate the boot loader by holding the three thumb 
buttons on your chorder (PB4, PB5 and PD6 grounded) while plugging
in the USB device. LED1 and LED3 should be constantly lit, indicating
that the boot loader is waiting for a command. Now the SpiffChorder
firmware can be written to the chorder by doing "make program" from
the top-level Makefile (provided you have the Makefile configured for
the usbasp programmer with avrdude. After programming, the boot loader
will automatically exit, and start the SpiffChorder application, which
should cause Windows to recognize the USB disconnect and connect of 
the SpiffChorder. If you need to program again, you must restart the
boot loader by unplugging the USB connection, holding the three thumb
buttons and plugging in the USB connection again.

For more information regarding the boot loader, look at the 
documentation in USBaspLoader.2008-02-05/spiffchorder.readme.txt.


Troubleshooting
---------------

This section will list a few things to try if you are having problems
getting the SpiffChorder working.

 * During startup all three LEDs light briefly when resetting the device.
   If this does not happen on your device, the SpiffChorder code is not
   operating properly. Make sure the crystal is connected correctly, and
   appropriate load capasitors are present. Also check the fuse settings
   and supply voltage. If using a 16MHz crystal you need to compile your
   own code - the shipped hex-file will not work. If the LEDs light for 
   about 4 seconds you are probably using the factory default ATmega168 
   clock configuration with CKDIV=8 enabled and running on the internal
   RC oscillator. If they light for about 3 seconds CKDIV=8 is likely
   enabled, but you are using external 12MHz crystal. In both cases you
   need to check the fuses. Note that PonyProg shows a tick-mark for a
   programmed fuse, which means the fuse value is 0. If in doubt, read 
   the data sheet carefully. Wrong fuse settings may cause your device 
   to no longer be programmable.

 * If Windows does not properly detect your device (i.e. it reports
   "Unknown device" or "a USB device has malfunctioned"), there may be
   problems with the fuse settings as well (check above). It can also
   be caused by the USB lines not being connected correctly. Make sure
   D+ and D- are connected as specified in circuit/chorder.png. Some
   motherboards have problems with voltage levels exceeding the specified
   3.3V on the data lines. Measure the voltage levels on D- of the USB 
   connector. It should be between 2.6V and 3.3V. If not, there seems to
   be a problem with the zener diodes.

 * If LED1 and LED3 are stedily lit after startup, you are probably in
   boot loader mode. Check the bootloader documentation. The boot loader
   shipped with SpiffChorder is triggered by holding the 3 thumb buttons
   while plugging in the device. This can happen if PB4, PB5 and PD6 are
   all low/grounded during startup.


Files
-----
readme.txt              This file.
changes.txt             What has been changed in the different versions.
doc.txt                 Extra documentation (for further development).
license.txt             The license this project is released under.
circuit/                Directory with circuit diagrams in PDF and PNG formats.
usbdrv/                 Directory with the V-USB driver.
keymaps/                Keyboard maps (chord maps).
Makefile                Build instructions for GNU Make.
main.c                  Main source code file.
main.hex                Compiled version, ready to be programmed into uC.
usbconfig.h             Configuration for V-USB stack.


License information
-------------------

The SpiffChorder project is based on Objective Development's HIDkeys demo 
application, which is released under the terms of the GNU GPL v2 or v3.

The SpiffChorder project is released under the terms of the GNU GLP v3.

Further more we strongly encurage any derivative work to disclose circuit
documentation.

See the file license.txt for details.


Copyright
---------

The SpiffChorder project and documentation is Copyright (C) 2006-2012
by Mikkel Holm Olsen (AKA Spaceman Spiff). More information about the
project can be found on http://symlink.dk/projects/spiffchorder/.

$Id$
