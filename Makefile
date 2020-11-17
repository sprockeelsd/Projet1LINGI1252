.PHONY: run clean perf all
.DEFAULT_GOAL := run

CC = gcc
OBJ = header.h reader-writer.c philosophers.c producer-consumer.c main.c -lpthread

all: run perf

run: $(OBJ)
	$(CC) $^ -o main -lpthread

perf: $(OBJ)
	rm -f datas.csv
	touch datas.csv
	bash script.sh > datas.csv
	python3 graphs.py

clean:
	rm -f main
