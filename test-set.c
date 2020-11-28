#include "header.h"

void *test_TS(void *arg){
	int j = 0;
	while(j < 6400/nbthread_TS) {
		j++;
		lock_TS(mutex_TS);
		while(rand()>RAND_MAX/10000);
		unlock(mutex_TS);
	}
	//printf("%d boucle numéro %d\n",*((int*)arg),j);
}

int main_TS(int threads){
	//initialisation du lock
	nbthread_TS = threads;
	mutex_TS = init();
	
	srand(getpid());
	//initialisation des threads
	pthread_t thread[threads];
	int id[threads];
	
	for(int i=0; i<threads; i++){
		id[i]=i+1;
	}
	for(int i=0; i<threads; i++){
		pthread_create(&thread[i], NULL, test_TS, (void*)&(id[i]));
	}

	for(int i=0; i<threads; i++){
		pthread_join(thread[i], NULL);
	}
	destroy(mutex_TS);		
}
