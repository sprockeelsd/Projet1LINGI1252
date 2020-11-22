#include "header.h"

void* post(semaphore *arg){
	if((*arg).current>=(*arg).max || (*arg).current<0) printf("ERROR 2\n");//pour tester
	else{
		if(*((*arg).mutex[(*arg).index])==0) printf("ERROR 3\n");//pour tester
		unlock((*arg).mutex[(*arg).index]);
		(*arg).current = (*arg).current+1;
		if((*arg).current==1) unlock((*arg).sem_mutex);
	}
}

void* wait(semaphore *arg){
	if((*arg).current==0) lock_TS((*arg).sem_mutex);//while or if???
	if((*arg).current==0) printf("ERROR 1\n");//pour tester si while ou if
	else{//else part avec le if de test
		for(long i=0; i<(*arg).max; i++){
			if(*((*arg).mutex[i])==0){
				(*arg).current = (*arg).current-1;
				lock_TS((*arg).mutex[i]);
				(*arg).index = i;
				return NULL;
			}
		}
	}
}

semaphore* init_S(int start, int maxi){//start is either 0 or maxi
	semaphore* arg = malloc(sizeof(semaphore));
	//init local int start
	(*arg).current = start;
	(*arg).max = maxi;
	//init mutex
	(*arg).mutex = malloc(maxi*sizeof(int));
	for(long i=0; i<maxi; i++){
		(*arg).mutex[i] = init();
	}
	//init general mutex
	(*arg).sem_mutex = init();
	return arg;
}

void* destroy_S(semaphore* arg){
	for(long i=0; i<(*arg).max; i++)
		destroy((*arg).mutex[i]);
	free((*arg).mutex);
	free(arg);
}
