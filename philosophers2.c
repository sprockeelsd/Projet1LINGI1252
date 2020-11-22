#include "header.h"
//gcc -o philosophers philosophers.c -lpthread

void* philosophe2(void* arg){
	int *id=(int *) arg;
	int left = *id;
	int right = (left + 1) % philosophess;
	int j = 0;
	while(j < 1000000) {
		//printf("Philosophe [%d] pense\n",*id);
		if(left<right){
			lock_TS(baguette2[left]);
			lock_TS(baguette2[right]);
		}
		else{
			lock_TS(baguette2[right]);
			lock_TS(baguette2[left]);
		}
		//printf("Philosophe [%d] mange et on est à la %d ème itération \n",*id,j);
		j++;   
		unlock(baguette2[left]);
		unlock(baguette2[right]);
	}
	//printf("philosophe [%d] a mangé %d fois \n",*id,j);
	return (NULL);
}

int main_P2(int philosophes){
	
	philosophess=philosophes;
	if(philosophes==1){
		philosophess=2;
	}
	pthread_t phil[philosophes];
	baguette2 = malloc(philosophess*sizeof(int));

	long i;
	int id[philosophes];

	srand(getpid());

	for (i = 0; i < philosophess; i++)
     		id[i]=i;

   	for (i = 0; i < philosophess; i++)
   		baguette2[i] = init();

   	for (i = 0; i < philosophes; i++)
     		pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );

   	for (i = 0; i < philosophes; i++)
      		pthread_join(phil[i], NULL);
	
	for (i = 0; i < philosophes; i++)
		destroy(baguette2[i]);
	free(baguette2);
   	return (EXIT_SUCCESS);
}
