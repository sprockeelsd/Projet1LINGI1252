#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2

echo "nb_coeur,temps"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		make clean -s 2> /dev/null
		output=$((/usr/bin/time -f %e make -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},${output}+0.01
	done
done
