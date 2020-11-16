.PHONY: run clean all
.DEFAULT_GOAL := run

CC = gcc
OBJ = header.h reader-writer.c philosophers.c producer-consumer.c main.c -lpthread

all: run perf

run: $(OBJ)
	$(CC) $^ -o main -lpthread

perf: $(OBJ)
	rm -f datas.csv
	bash script.sh > datas.csv
	python3 python_graphs.py

clean:
	rm -f main
	rm -f data.csv
