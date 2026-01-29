#!/bin/bash

echo "+++compiling main.cpp: +++"
cmake -S . -B ./build

echo "+++-----------------------------------+++"

cd ./build
make
cd ../
