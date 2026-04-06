#!/usr/bin/env bash


mkdir ./bin

for file in ../src/*; do
  gcc 
done


gcc -c $srcFile -o $objectFile
ar rcs $staticLib $objectFile
rm $objectFile