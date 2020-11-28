#include "header.h"

void* post(semaphore *arg){
	lock_TS(arg->mutexP); //b sem.c:4 (pour le debug)
	while(arg->current==arg->max); //pas de threads actifs
	lock_TS(arg->protection); 
	arg->current = arg->current+1; //une place en plus de libre
	unlock(arg->protection); //next thread peut entrer 
	unlock(arg->mutexP); //next post peut entrer
}

void* wait(semaphore *arg){
	lock_TS(arg->mutexW); 
	while(arg->current==0); //plus de places libres
	lock_TS(arg->protection);
	arg->current = arg->current-1; //une place en moins de libre
	unlock(arg->protection); //next thread peut entrer 
	unlock(arg->mutexW); //next wait peut entrer
}

semaphore* init_S(int start, int maxi){//normalement start vaut soit 0 soit maxi
	semaphore* arg = malloc(sizeof(semaphore));
	//init local
	arg->current = start; //l'état de la sémaphore
	arg->max = maxi; //valeur pour emêcher de faire trop d'appels a post
	arg->mutexW = init(); //un thread rentre dans wait à la fois
	arg->mutexP = init(); //un thread rentre dans post à la fois
	arg->protection = init(); //un thread modifie l'état d'un sémaphore à la fois
	return arg;
}

void* destroy_S(semaphore* arg){
	destroy(arg->mutexW);
	destroy(arg->mutexP);
	destroy(arg->protection);
	free(arg);
}
