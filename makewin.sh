#!/bin/bash

i586-mingw32msvc-g++ -O3 *.cpp -o he2.exe -I ~/Applications/freeglut/include/ -L ~/Applications/freeglut/lib/ -lopengl32 -lfreeglut -lglu32
strip he2.exe
