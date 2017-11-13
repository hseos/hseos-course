#! /bin/bash

PROG=../hello

count=0
for name in ???.dat
do
    outname=${name/.dat/.out}
    corrname=${name/.dat/.ans}
    echo $name $outname
    $PROG < $name > $outname && diff -w $outname $corrname && count=$((count+1))
done
echo "Tests passed: " $count

