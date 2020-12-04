#!/usr/bin/bash
RUNS=5
let NTHREAD=$(nproc)*2
declare -i one
declare -i two

echo "N° of threads,empty,Philosophers,Producer/Consumer,Reader/Writer,N1,N2"

#ce code en shell teste les trois algorithmes de la partie 1 du projet
make -s 2> /dev/null
for ((i=0;i<$RUNS;i++))
do
	for ((n=1;n<=$NTHREAD;n++))
	do
		one=n/2
		two=(n-1)/2+1
		output2=$((/usr/bin/time -f %e ./main -P ${n} -j ${n} -s 2>&1)| cut -d\) -f2)
		output3=$((/usr/bin/time -f %e ./main -PC ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		output4=$((/usr/bin/time -f %e ./main -RW ${one} ${two} -j ${n} -s 2>&1)| cut -d\) -f2)
		echo ${n},0,${output2},${output3},${output4},${one},${two}
	done
done
