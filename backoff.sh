#!/usr/bin/bash
RUNS=1000
Times=1000
declare -i min
declare -i max

echo "Vmin,empty,BTTS_1,BTTS_2,BTTS_3"

for ((i=0;i<$RUNS;i++))
do
	for ((i=0;i<$Times;i+=10))
	do
		min=${i}
		max=${i}
		output=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
		max=${i}*100
		output1=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
		max=${i}*100000
		output2=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${i},0,${output},${output1},${output2}
	done
done
