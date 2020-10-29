#!/bin/sh

mkdir -p my_tanks_game/usr/bin/
cp ../../build_ubuntu/tanks_game my_tanks_game/usr/bin/

dpkg-deb --build my_tanks_game
mv my_tanks_game.deb my_tanks_game-0.0.1_amd64.deb

tar -zcvf my_tanks_game-0.0.1_amd64.deb.tar.gz my_tanks_game-0.0.1_amd64.deb