.PHONY: run clean perf1 all
.DEFAULT_GOAL := run

CC = gcc
OBJ = header.h reader-writer.c philosophers.c producer-consumer.c main.c -lpthread

all: run perf1 perf2

run: $(OBJ)
	$(CC) $^ -o main -lpthread

perf1: $(OBJ)
	touch datas.csv
	bash perf_partie1.sh > datas.csv
	python3 graphs.py
	rm -f datas.csv
	
perf2: $(OBJ)
	touch datas.csv
	bash perf_partie2.sh > datas.csv
	python3 verrou.py
	rm -f datas.csv

clean:
	rm -f main
	#rm -f datas.csv
