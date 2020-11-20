#include "header.h"

void *test_TTS(void *arg){
	int j = 0;
	while(j < 6400/nbthread_TTS) {
		j++;
		lock_TTS(mutex_TTS);
		while(rand()>RAND_MAX/10000);
		unlock(mutex_TTS);
	}
	//printf("%d boucle numéro %d\n",*((int*)arg),j);
}

int main_TTS(int threads){
	//initialisation du lock
	nbthread_TTS = threads;
	mutex_TTS = init();
	
	srand(getpid());
	
	pthread_t thread[threads];
	
	int id[threads];
	
	for(int i=0; i<threads; i++){
		id[i]=i+1;
	}
	for(int i=0; i<threads; i++){
		pthread_create(&thread[i], NULL, test_TTS, (void*)&(id[i]));
	}

	for(int i=0; i<threads; i++){
		pthread_join(thread[i], NULL);
	}
	destroy(mutex_TTS);		
}
