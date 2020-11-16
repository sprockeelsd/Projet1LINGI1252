.PHONY: run clean all

CC = gcc

all:	header.h reader-writer.c philosophers.c producer-consumer.c main.c -lpthread
	$(CC) header.h reader-writer.c philosophers.c producer-consumer.c main.c -o main -lpthread
	
philosophers: header.h reader-writer.c philosophers.c producer-consumer.c main.c -lpthread
	$(CC) -o philosphers header.h philosophers.c -lpthread

run: header.h mainFact.c multithreading.c wheelFactorization.c queuing.c
	$(CC) header.h mainFact.c multithreading.c wheelFactorization.c queuing.c -lpthread -lm -std=c99 -o fact

performance_test: performance_test.c header.h wheelFactorization.c queuing.c multithreading.c
	$(CC) performance_test.c header.h wheelFactorization.c queuing.c multithreading.c -lpthread -o performance_test

run_perf: performance_test.c header.h wheelFactorization.c queuing.c multithreading.c performance_test
	rm -f data.csv
	python3 python_graphs.py
	./performance_test

clean:
	rm -f main
	rm -f philosophers
	rm -f reader-writer
	rm -f producer-consumer
