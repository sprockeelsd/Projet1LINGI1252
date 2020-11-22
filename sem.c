#include "header.h"

void* post(semaphore *arg){
	printf("CHECK P1\n");
	printf("current=%d\n",*(arg->current));
	printf("CHECK P1b\n");
	if(*(arg->current)>=*(arg->max) || *(arg->current)<0) printf("ERROR 2\n");//pour tester
	else{
		printf("CHECK P2\n");
		for(long i=0; i<*(arg->max); i++){
			if(*(arg->mutex[i])==0){
				unlock(arg->mutex[i]);
				*(arg->current) = *(arg->current)+1;
				if(*(arg->current)==1) unlock(arg->sem_mutex);
				printf("CHECK P3\n");
				return NULL;
			}
		}
	}
}

void* wait(semaphore *arg){
	printf("CHECK W1\n");
	printf("current-%d\n",*(arg->current));
	if(*(arg->current)==0) lock_TS(arg->sem_mutex);//while or if???
	if(*(arg->current)==0) printf("ERROR 1\n");//pour tester si while ou if
	else{//else part avec le if de test
		printf("CHECK W2\n");
		for(long i=0; i<*(arg->max); i++){
			if(*(arg->mutex[i])==0){
				*(arg->current) = *(arg->current)-1;
				lock_TS(arg->mutex[i]);
				printf("CHECK W3\n");
				return NULL;
			}
		}
	}
}

semaphore* init_S(int start, int maxi){//start is either 0 or maxi
	semaphore* arg = malloc(sizeof(semaphore));
	//init local int start
	arg->current = malloc(sizeof(int));
	arg->max = malloc(sizeof(int));
	*(arg->current) = start;
	*(arg->max) = maxi;
	//init mutex
	arg->mutex = malloc(maxi*sizeof(int));
	for(long i=0; i<maxi; i++){
		arg->mutex[i] = init();
	}
	//init general mutex
	arg->sem_mutex = init();
	return arg;
}

void* destroy_S(semaphore* arg){
	for(long i=0; i<*(arg->max); i++){
		printf("CHECK END1\n");
		while(rand()>RAND_MAX/10000);
		destroy(arg->mutex[i]);
	}
	printf("CHECK END2\n");
	free(arg->mutex);
	printf("CHECK END3\n");
	free(arg);
}
