make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DGOODTIMES=1 -DCARMACIZED=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
/Applications/ffmpeg -i ./images/Tile.png -f rawvideo -pix_fmt rgb565 ./images/tile.raw
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Full_ID_ACTIVISION_1_4.fw
mv firmware.fw ./release/Wolf3D_Full_ID_ACTIVISION_1_4.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DAPOGEE_1_1=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Full_APOGEE_1_1.fw
mv firmware.fw ./release/Wolf3D_Full_APOGEE_1_1.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Full_APOGEE_1_4.fw
mv firmware.fw ./release/Wolf3D_Full_APOGEE_1_4.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DUPLOAD=1 -DAPOGEE_1_0=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Shareware_1_0.fw
mv firmware.fw ./release/Wolf3D_Shareware_1_0.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DUPLOAD=1 -DAPOGEE_1_1=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Shareware_1_1.fw
mv firmware.fw ./release/Wolf3D_Shareware_1_1.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DUPLOAD=1 -DAPOGEE_1_2=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Shareware_1_2.fw
mv firmware.fw ./release/Wolf3D_Shareware_1_2.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DUPLOAD=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D_Shareware_1_4.fw
mv firmware.fw ./release/Wolf3D_Shareware_1_4.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DGOODTIMES=1 -DCARMACIZED=1 -DSPEAR=1 -DDATADIR="\"/sd/data/Spear Of Destiny/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
/Applications/ffmpeg -i ./images/TileSOD.png -f rawvideo -pix_fmt rgb565 ./images/tileSOD.raw
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw SpearOfDestiny ./images/tileSOD.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Spear\ Of\ Destiny.fw
mv firmware.fw ./release/Spear\ Of\ Destiny.fw

make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DCARMACIZED=1 -DSPEAR=1 -DSPEARDEMO=1 -DDATADIR="\"/sd/data/Spear Of Destiny/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw SpearOfDestiny ./images/tileSOD.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Spear\ Of\ Destiny\ Demo.fw
mv firmware.fw ./release/Spear\ Of\ Destiny\ Demo.fw