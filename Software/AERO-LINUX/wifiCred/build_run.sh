#!/bin/bash

echo "+++compiling main.cpp+++"


cd ./build
make || exit 1
echo "+++----------Executing SONO--------------+++"
# sudo ./SONO
./AERO
cd ../
