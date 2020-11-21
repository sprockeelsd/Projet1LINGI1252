#include "header.h"

void* post(semaphore *arg){
	if((*arg).current>0){
		//dequeue??
		lock_TS((*arg).mutex[(*arg).current]);
	}
	else{
		unlock((*arg).mutex[(*arg).current]);
		(*arg).current = (*arg).current+1;
	}
}

void* wait(semaphore *arg){
	if(*((*arg).mutex[(*arg).current])==1){
		//enqueue??
	}else{
		(*arg).current = (*arg).current-1;
		if((*arg).current == 0){lock_TS((*arg).mutex[(*arg).current]);}
	}
}

semaphore* init_S(int maxi){
	semaphore* arg = malloc(sizeof(semaphore));
	//init local int start
	(*arg).current = maxi;
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
