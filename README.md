# Wolf4SDL ESP32 Port
by Gadget Workbench

Demo video:

(https://youtu.be/QCEx_Ir7iFU)

Credits:
--------

Wolf4SDL by Moritz "Ripper" Kroll (http://www.chaos-software.de.vu)
Original Wolfenstein 3D by id Software (http://www.idsoftware.com)

Wolf4SDL is an open-source port of id Software's classic first-person shooter
Wolfenstein 3D to the cross-plattform multimedia library "Simple DirectMedia
Layer (SDL)" (http://www.libsdl.org). It is meant to keep the original feel
while taking advantage of some improvements.

Installation:
-------------

<b>Wolfenstein 3D</b>

Game Data:

- Put the game data for Wolfenstein 3D Full v1.4 GT/ID/Activision version in the folder:
    /sd/data/Wolfenstein 3D/base/

Note - this is the same version and folder structure as the Steam version of Wolfenstein 3D.  (https://store.steampowered.com/app/2270/Wolfenstein_3D/)

Firmware:

- Place the <b>Wolf3D.fw</b> file on your Odroid-Go SD card in the /odroid/firmware/ folder.
- Power off the ODROID-GO, hold B, and power on the ODROID-GO.
- When the ODROID-GO menu displays, select Duke3D, press A, then press Start.



Licenses:
---------

 - The original source code of Wolfenstein 3D: license-id.txt
 - The OPL2 emulator (fmopl.cpp): license-mame.txt
 - ESP32 Parts by me are licensed under GNU General Public License v2.0 (see LICENSE).
 - SDL - Simple DirectMedia Layer license - see: /components/SDL/LICENSE
 - SDL-Mixer - GNU LESSER GENERAL PUBLIC LICENSE - see: /components/SDL_mixer-1.2.12/COPYING
