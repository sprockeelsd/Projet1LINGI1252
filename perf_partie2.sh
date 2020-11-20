#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2
declare -i one
declare -i two

echo "N° of threads,temps_CC,Test-Set,Test-Test-Set,Backoff-Test-Test-Set,N1,N2"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		one=n/2
		two=(n-1)/2+1
		make clean -s 2> /dev/null
		output1=$((/usr/bin/time -f %e make -j ${n} -s 2>&1)| cut -d\) -f2)
		output2=$((/usr/bin/time -f %e ./main -TS ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -TTS ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		#output4=$((/usr/bin/time -f %e ./main -BTTS ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},${output1},${output2},${output3},0,${one},${two} #${output4},${one},${two}
	done
done
