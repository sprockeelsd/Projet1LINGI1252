.PHONY: clean perf1 all
.DEFAULT_GOAL := main

CC = gcc
OBJ = header.h reader-writer.c philosophers.c producer-consumer.c reader-writer2.c philosophers2.c producer-consumer2.c verrou.c sem.c test-set.c test-test-set.c backoff-test-test-set.c main.c 

all: run perf1 perf2

main: $(OBJ)
	$(CC) $^ -o main -lpthread

a.out: $(OBJ)
	$(CC) -g $^ -lpthread
	gdb a.out
	

perf1: main
	touch datas.csv
	bash perf_partie1.sh > datas.csv
	python3 graphs.py
	rm -f datas.csv
	
perf2: main
	touch datas.csv
	bash perf_partie2.sh > datas.csv
	python3 graphs.py
	rm -f datas.csv

perfb: main
	touch datas.csv
	bash backoff.sh > datas.csv
	python3 python3 backoffs.py
	rm -f datas.csv
	
clean:
	rm -f main
	rm -f header.h.gch
