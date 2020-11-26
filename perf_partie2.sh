#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2

echo "N° of threads,temps_CC,Test-Set,Test-Test-Set,Backoff-Test-Test-Set"

for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		make clean -s 2> /dev/null
		output1=$((/usr/bin/time -f %e make -j ${n} -s 2>&1)| cut -d\) -f2)
		output2=$((/usr/bin/time -f %e ./main -TS ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -TTS ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output4=$((/usr/bin/time -f %e ./main -BTTS ${n} 20 100000 -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},${output1},${output2},${output3},${output4}
	done
done
