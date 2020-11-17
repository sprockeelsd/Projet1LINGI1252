#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2
declare -i one
declare -i two

echo "nb_coeur,temps_CC,temps_P,temps_PC,temps_RW"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		one=n/2
		two=n/2+1
		make clean -s 2> /dev/null
		output1=$((/usr/bin/time -f %e make -j ${n} -s 2>&1)| cut -d\) -f2)
		output2=$((/usr/bin/time -f %e ./main -P ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -PC ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		output4=$((/usr/bin/time -f %e ./main -RW ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},${output1},${output2},${output3},${output4}
	done
done
