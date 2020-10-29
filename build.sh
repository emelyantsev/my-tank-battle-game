#!/bin/sh

cd build_ubuntu

g++ -c ../src/*.cpp
g++ *.o -o tanks_game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

cd -