#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2

echo "N° of threads,empty,Test-Set,Test-Test-Set,Backoff-Test-Test-Set"

#ce code en shell teste les trois implémentations de nos verrous
make -s 2> /dev/null
for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		output2=$((/usr/bin/time -f %e ./main -TS ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -TTS ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output4=$((/usr/bin/time -f %e ./main -BTTS ${n} 20 100000 -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},0,${output2},${output3},${output4}
	done
done
