#!/bin/sh

cd build_ubuntu

g++ -c ../src/*.cpp
g++ *.o -o game.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

cd -