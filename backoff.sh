#!/usr/bin/bash
RUNS=10000
declare -i min
declare -i max

make
echo "Vmin,BTTS_1,BTTS_2,BTTS_3,BTTS_4,BTTS_5,BTTS_6,BTTS_7"

for ((i=0;i<$RUNS;i+=100))
do
	min=${i}
	max=${i}
	output=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*10
	output1=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*100
	output2=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*1000
	output3=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*10000
	output4=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*100000
	output5=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	max=${i}*1000000
	output6=$((/usr/bin/time -f %e ./main -BTTS 8 ${min} ${max} -j ${n} -s 2>&1)| cut -d\) -f2)
	echo ${i},${output},${output1},${output2},${output3},${output4},${output5},${output6}
done
