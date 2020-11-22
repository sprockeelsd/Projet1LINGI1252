#include "header.h"
//gcc -o philosophers philosophers.c -lpthread

void* philosophe (void* arg){
	int *id=(int *) arg;
	int left = *id;
	int right = (left + 1) % philosophess;
	int j = 0;
	while(j < 1000000) {
		//printf("Philosophe [%d] pense\n",*id);
		if(left<right){
			pthread_mutex_lock(&baguette[left]);
			pthread_mutex_lock(&baguette[right]);
		}
		else{
			pthread_mutex_lock(&baguette[right]);
			pthread_mutex_lock(&baguette[left]);
		}
		//printf("Philosophe [%d] mange et on est à la %d ème itération \n",*id,j);
		j++;   
		pthread_mutex_unlock(&baguette[left]);
		pthread_mutex_unlock(&baguette[right]);
	}
	//printf("philosophe [%d] a mangé %d fois \n",*id,j);
	return (NULL);
}

int main_P(int philosophes){
	
	philosophess=philosophes;
	if(philosophes==1){
		philosophess=2;
	}
	pthread_t phil[philosophes];
	baguette = malloc(philosophess*sizeof(pthread_mutex_t));

	long i;
	int id[philosophes];

	srand(getpid());

	for (i = 0; i < philosophess; i++)
     		id[i]=i;

   	for (i = 0; i < philosophess; i++)
      		pthread_mutex_init(&baguette[i], NULL);

   	for (i = 0; i < philosophes; i++)
     		pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );

   	for (i = 0; i < philosophes; i++)
      		pthread_join(phil[i], NULL);
	
	for (i = 0; i < philosophes; i++)
      		pthread_mutex_destroy(&baguette[i]);
      	
	free(baguette);
   	return (EXIT_SUCCESS);
}
