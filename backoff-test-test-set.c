#include "header.h"

void *test_BTTS(void *arg){
	int j = 0;
	while(j < 6400/nbthread_BTTS) {
		j++;
		//printf("%d boucle numéro %d\n",*((int*)arg),j);
		lock_BTTS(mutex_BTTS);
		while(rand()>RAND_MAX/10000);
		unlock(mutex_BTTS);
	}
	//printf("%d boucle numéro %d\n",*((int*)arg),j);
}

int main_BTTS(int threads, int min, int max){
	//initialisation du lock
	nbthread_BTTS = threads;
	mutex_BTTS = init();
	init_BTTS(min, max);
	
	srand(getpid());
	
	pthread_t thread[threads];
	
	int id[threads];
	
	for(int i=0; i<threads; i++){
		id[i]=i+1;
	}
	for(int i=0; i<threads; i++){
		pthread_create(&thread[i], NULL, test_BTTS, (void*)&(id[i]));
	}
	for(int i=0; i<threads; i++){
		pthread_join(thread[i], NULL);
	}
	destroy(mutex_BTTS);
}
