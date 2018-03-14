#!/bin/bash                                                                                                                               
cd build
module load opencv
cmake ../ -DCMAKE_CXX_COMPILER=/usr/bin/g++
cd ../
