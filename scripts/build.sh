#!/usr/bin/env bash

gcc -c -Iinclude -Wall -fPIC main.c -o main.o
gcc -shared -o libAidan.so main.o
mv libAidan.so /usr/lib/
chmod 0755 /usr/lib/libAidan.so
ldconfig

libdir=/usr/include/LibAidan

mkdir -p $libdir

for file in ./include/*.h; do
  cp $file $libdir
done