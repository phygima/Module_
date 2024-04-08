#!/bin/bash
gcc -c -fPIC contact.c -o contact.o
gcc -c -fPIC contact_info.c  -o contact_info.o
gcc -c -fPIC personal_info.c -o personal_info.o
gcc -c -fPIC main.c -o main.o


gcc -shared -o libcontacts.so contact.o contact_info.o personal_info.o main.o


