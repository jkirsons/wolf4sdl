make clean
make -j2 EXTRA_CPPFLAGS='-DVERSIONALREADYCHOSEN=1 -DGOODTIMES=1 -DCARMACIZED=1 -DDATADIR="\"/sd/data/Wolfenstein 3D/base/\"" -DPLAYDEMOLIKEORIGINAL=1 -DDEMOSEXTERN=1 -DARTSEXTERN=1'
#cd release
/Applications/ffmpeg -i ./images/Tile.png -f rawvideo -pix_fmt rgb565 ./images/tile.raw
#~/Documents/GitHub/odroid-go-firmware/tools/mkfw/mkfw Duke3D ./images/tile.raw 0 16 1048576 app ./build/Duke3D.bin
#rm Duke3D-snd.fw
#mv firmware.fw Duke3D-snd.fw

~/Documents/GitHub/odroid-go-firmware-20181001/tools/mkfw/mkfw Wolf3D ./images/tile.raw 0 16 1048576 app ./build/Wolf3D.bin
rm ./release/Wolf3D.fw
mv firmware.fw ./release/Wolf3D.fw
