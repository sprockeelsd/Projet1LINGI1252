#include "header.h"

void* post(int *arg){
	//waiting until start<max
	//start++
	//if start==max --> block
	//if start==1 --> unblock
}

void* wait(int *arg){
	//waiting until start>0
	//start--
	//if start==0 --> block
	//if start==max-1 --> unblock
}

int* init(int start, int max){
	int *arg = malloc(sizeof(int));
	*arg = 0;
	//initiate local int start
	//initiate local int max
	return arg;
}

void* destroy(int* arg){
	free(arg);
}
