#include "header.h"

void* post(int *arg){
	//waiting until start<max
	//start++
	//if start==max --> block
	//if start==1 --> unblock
	
	//
}

void* wait(int *arg){
	//waiting until start>0
	//start--
	//if start==0 --> block
	//if start==max-1 --> unblock
}

int* init_S(int start, int max){
	semaphore *arg = malloc(sizeof(semaphore));
	//initiate local int start
	*arg->ncurrent = start;
	//initiate local int max
	*arg->nmax = max;
	//initiate queue
	*arg->queue = malloc(sizeof(void*));
	return arg;
}

void* destroy_S(int* arg){
	free(arg);
}
