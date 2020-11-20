.PHONY: clean perf1 all
.DEFAULT_GOAL := main

CC = gcc
OBJ = header.h reader-writer.c philosophers.c producer-consumer.c verrou.c test-set.c test-test-set.c main.c 

all: run perf1 perf2

main: $(OBJ)
	$(CC) $^ -o main -lpthread

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
	
clean:
	rm -f main
