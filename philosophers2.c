#include "header.h"
//gcc -o philosophers philosophers.c -lpthread

void* philosophe2(void* arg){
	printf("%d CHECK ENTER\n",*((int*)arg));
	int *id=(int *) arg;
	int left = *id;
	int right = (left + 1) % philosophess;
	int j = 0;
	printf("%d CHECK ENTRY\n",*id);
	while(j < 1000000) {
		//printf("Philosophe [%d] pense\n",*id);
		if(left<right){
			printf("%d CHECK 10\n",*id);
			lock_TS(baguette2[left]);
			lock_TS(baguette2[right]);
			printf("%d CHECK 20\n",*id);
		}
		else{
			printf("%d CHECK 30\n",*id);
			lock_TS(baguette2[right]);
			lock_TS(baguette2[left]);
			printf("%d CHECK 40\n",*id);
		}
		//printf("Philosophe [%d] mange et on est à la %d ème itération \n",*id,j);
		j++;
		printf("%d CHECK 50\n",*id);
		unlock(baguette2[left]);
		unlock(baguette2[right]);
		printf("%d CHECK 60\n",*id);
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

	printf("CHECK 1\n");
   	for (i = 0; i < philosophes; i++){
   		printf("CHECK WTF\n");
      		pthread_join(phil[i], NULL);
	}
	printf("CHECK 2\n");
	for (i = 0; i < philosophes; i++)
		destroy(baguette2[i]);
	printf("CHECK 3\n");
	free(baguette2);
	printf("CHECK 4\n");
   	return (EXIT_SUCCESS);
}
