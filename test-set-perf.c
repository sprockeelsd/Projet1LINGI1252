#include "header.h"

void *test(void *arg){
	int j = 0;
	while(j < 10) {
		j++;
		lock(mutex_TSP);
		while(rand()>RAND_MAX/10000);
		printf("%d boucle numéro %d\n",*((int*)arg),j);
		unlock(mutex_TSP);
	}
	return (NULL);
}


int main_TSP(int n){
	//initialisation du lock
	
	init_TS(mutex_TSP);
	
	srand(getpid());
	
	pthread_t thread[n];
		
	int id[n];
	
	for(int i=0; i<n; i++){
		id[i]=i+1;
	}
	for(int i = 0; i < n; i++){
		pthread_create(&thread[i], NULL, test, (void*)&(id[i]));
	}

	for(int i = 0; i < n; i++){
		pthread_join(thread[i], NULL);
	}
	destroy(mutex_TSP);	
	
}

