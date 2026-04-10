#!/usr/bin/env bash

./scripts/test_fast.sh

gcc -c -Iinclude -Wall -fPIC main.c -o main.o
gcc -shared -o libAidan.so main.o
sudo mv libAidan.so /usr/lib/
sudo ldconfig

libdir=/usr/include/LibAidan

sudo mkdir -p $libdir

for file in ./include/*.h; do
  sudo cp $file $libdir
done