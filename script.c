#!/usr/bin/bash
if [ $# -ne 1 ]; then
    echo "Il faut un argument"
    exit 2
fi

if [ -z "$( find $1 -name Makefile )" ]; then
    echo "Pas de Makefile"
else
    cd "$( dirname "$( find $1 -name Makefile )" )"
    make clean
    cd -
fi

date --rfc-3339 seconds > manifest.txt

find $1 -name *.c > f.txt
find $1 -name *.h >> f.txt
find $1 -name *.py >> f.txt
cat f.txt | while read line || [[ -n $line ]];
do
    echo "$(wc -l < $line)" >> n.txt
done

((tot=0))
cat n.txt | while read line || [[ -n $line ]];
do
    ((tot=$tot+$line))
    echo $tot > end.txt
done

cat end.txt >> manifest.txt

echo "$(whoami)@$(hostname)" >> manifest.txt

rm f.txt n.txt end.txt

tar -cJf "$(basename $1)".tar.xz $1 manifest.txt

rm manifest.txt
exit 0


#!/bin/bash
RUNS=5
NTHREAD=8

echo "nb_coeur,temps"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		make clean -s 2> /dev/null
		output=$((/usr/bin/time -f %e make -j ${n} -s 2>&1) | cut -d\) -f2)
		echo ${n},${output:1}
	done
done
