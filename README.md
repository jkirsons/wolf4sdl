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

SD Card: /data/Wolfenstein 3D/base/

Note - this is the same version and folder structure as the Steam version of Wolfenstein 3D.  (https://store.steampowered.com/app/2270/Wolfenstein_3D/)

Firmware:

- Place the <b>Wolf3D.fw</b> file on your Odroid-Go SD card in the /odroid/firmware/ folder.
- Power off the ODROID-GO, hold B, and power on the ODROID-GO.
- When the ODROID-GO menu displays, select Wolf3D, press A, then press Start.


<b>Spear of Destiny</b>

Game Data:

- Put the game data for Spear of Destiny Full and Mission Disks in the folder:
SD Card: /data/Spear Of Destiny/base/

Note - this is the same version and folder structure as the Steam version of Spear Of Destiny.  (https://store.steampowered.com/app/9000/Spear_of_Destiny/)

Firmware:

- Place the <b>Spear Of Destiny.fw</b> file on your Odroid-Go SD card in the /odroid/firmware/ folder.
- Power off the ODROID-GO, hold B, and power on the ODROID-GO.
- When the ODROID-GO menu displays, select Spear Of Destiny, press A, then press Start.

Mission Packs:

- Hold Select during power on for Mission 2: Return to Danger
- Hold Start during power on for Mission 3: Ultimate Challenge

Sample folder format for the mission packs:
```
/data/Spear Of Destiny/base/vswap.sod
/data/Spear Of Destiny/base/vswap.sd1
/data/Spear Of Destiny/base/vswap.sd2

/data/Spear Of Destiny/base/gamemaps.sod
/data/Spear Of Destiny/base/gamemaps.sd1
/data/Spear Of Destiny/base/gamemaps.sd2

/data/Spear Of Destiny/base/maphead.sod
/data/Spear Of Destiny/base/maphead.sd1
/data/Spear Of Destiny/base/maphead.sd2
```

Licenses:
---------

 - The original source code of Wolfenstein 3D: license-id.txt
 - The OPL2 emulator (fmopl.cpp): license-mame.txt
 - ESP32 Parts by me are licensed under GNU General Public License v2.0 (see LICENSE).
 - SDL - Simple DirectMedia Layer license - see: /components/SDL/LICENSE
 - SDL-Mixer - GNU LESSER GENERAL PUBLIC LICENSE - see: /components/SDL_mixer-1.2.12/COPYING
