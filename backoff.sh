#!/usr/bin/bash
RUNS=5
Times=1000
declare -i min
declare -i max1
declare -i max2
declare -i max3

#ce code en shell teste le verrou en backoff avec différents temps d'attente minimun et maximum
echo "Vmin,empty,BTTS_1,BTTS_2,BTTS_3"
make -s 2> /dev/null
for ((i=0;i<$RUNS;i++))
do
	for ((k=1;k<$Times;k+=50))
	do
		min=${k}
		max1=${k}*5
		output=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j 8 -s 2>&1)| cut -d\) -f2)
		max2=${k}*100
		output1=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j 8 -s 2>&1)| cut -d\) -f2)
		max3=${k}*10000
		output2=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j 8 -s 2>&1)| cut -d\) -f2)
		echo ${k},0,${output},${output1},${output2}
	done
done
