#include "header.h"

void* post(semaphore *arg){
	if(*(arg->current)>*(arg->max) || *(arg->current)<0) printf("ERROR 1\n");//pour tester
	lock_TS(arg->mutexP); //un thread modifie current a la fois
	while(*(arg->current)==*(arg->max)); //pas de threads actifs
	lock_TS(arg->protection); //un thread modifie current a la fois
	*(arg->current) = *(arg->current)+1; //une place en plus de libre
	unlock(arg->protection); //next thread peut entrer 
	unlock(arg->mutexP); //next post can enter
}

void* wait(semaphore *arg){
	if(*(arg->current)>*(arg->max) || *(arg->current)<0) printf("ERROR 2\n");//pour tester
	lock_TS(arg->mutexW); //un thread modifie current a la fois
	while(*(arg->current)==0); //plus de places libres
	lock_TS(arg->protection); //un thread modifie current a la fois
	*(arg->current) = *(arg->current)-1; //une place en moins de libre
	unlock(arg->protection); //next thread peut entrer 
	unlock(arg->mutexW); //next wait can enter
}

semaphore* init_S(int start, int maxi){//start is either 0 or maxi
	semaphore* arg = malloc(sizeof(semaphore));
	//init local
	arg->current = malloc(sizeof(int));
	arg->max = malloc(sizeof(int));
	arg->mutexW = malloc(sizeof(int));
	arg->mutexP = malloc(sizeof(int));
	arg->protection = malloc(sizeof(int));
	*(arg->current) = start;
	*(arg->max) = maxi;
	arg->mutexW = init();
	arg->mutexP = init();
	arg->protection = init();
	return arg;
}

void* destroy_S(semaphore* arg){
	free(arg->max);
	free(arg->current);
	free(arg->mutexP);
	free(arg->mutexW);
	free(arg->protection);
	free(arg);
}
