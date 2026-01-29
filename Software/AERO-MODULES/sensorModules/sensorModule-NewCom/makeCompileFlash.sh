#!/bin/bash

echo "+++compiling project+++"


cd ./build
make || exit 1
echo "+++----------Flashing AERO-MODULE--------------+++"
openocd -f interface/raspberrypi-swd.cfg -f target/rp2040.cfg -c "adapter speed 100" -c "program sensorModule-TEST_ENV.elf verify reset exit" 
cd ../
