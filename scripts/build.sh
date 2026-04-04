objectFile="ctmpl.o"
staticLib="bin/ctmpl.a"
srcFile="ctmpl.c"

mkdir ./bin

gcc -c $srcFile -o $objectFile
ar rcs $staticLib $objectFile
rm $objectFile