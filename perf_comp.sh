#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2
declare -i one
declare -i two

echo "N° of threads,temps_CC,Philosophers,Producer/Consumer,Reader/Writer,Philosophers2,Producer/Consumer2,Reader/Writer2,N1,N2"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		one=n/2
		two=(n-1)/2+1
		make clean -s 2> /dev/null
		output1=$((/usr/bin/time -f %e make -j ${n} -s 2>&1)| cut -d\) -f2)
		output2=$((/usr/bin/time -f %e ./main -P ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -PC ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		output4=$((/usr/bin/time -f %e ./main -RW ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		output5=$((/usr/bin/time -f %e ./main -P2 ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output6=$((/usr/bin/time -f %e ./main -PC2 ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		output7=$((/usr/bin/time -f %e ./main -RW2 ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},${output1},${output2},${output3},${output4},${output5},${output6},${output7},${one},${two}
	done
done
