#!/bin/bash

gcc -shared -o libadd.so add.c
gcc -shared -o libdivide.so divide.c
gcc -shared -o libmultiply.so multiply.c
gcc -shared -o libsubtract.so subtract.c

gcc main.c -o calculator -ldl -Wl,-rpath=. -L. -ladd -ldivide -lmultiply -lsubtract

./calculator
