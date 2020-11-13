#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define PHILOSOPHES 10

//gcc -o philosophers philosophers.c -lpthread
pthread_t phil[PHILOSOPHES];
pthread_mutex_t baguette[PHILOSOPHES];

void* philosophe ( void* arg ){
	int *id=(int *) arg;
	int left = *id;
	int right = (left + 1) % PHILOSOPHES;
	int j = 0;
	while(j < 10000) {
		//printf("Philosophe [%d] pense\n",*id);
		if(left<right){
			pthread_mutex_lock(&baguette[left]);
			//printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);
			pthread_mutex_lock(&baguette[right]);
			//printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);
		}
		else{
			pthread_mutex_lock(&baguette[right]);
			//printf("Philosophe [%d] possède baguette droite [%d]\n",*id,right);
			pthread_mutex_lock(&baguette[left]);
			//printf("Philosophe [%d] possède baguette gauche [%d]\n",*id,left);
		}
		//printf("Philosophe [%d] mange et on est à la %d ème itération \n",*id,j);
		
		j++;   
		pthread_mutex_unlock(&baguette[left]);
		//printf("Philosophe [%d] a libéré baguette gauche [%d]\n",*id,left);
		pthread_mutex_unlock(&baguette[right]);
		//printf("Philosophe [%d] a libéré baguette droite [%d]\n",*id,right);  
	}
	//printf("philosophe [%d] a mangé %d fois \n",*id,j);
	return (NULL);
}

int main ( int argc, char *argv[])
{
	//faire en sorte que la fonction prenne le nombre de philosophes en argument
	long i;
	int id[PHILOSOPHES];

	srand(getpid());

	for (i = 0; i < PHILOSOPHES; i++)
     		id[i]=i;

   	for (i = 0; i < PHILOSOPHES; i++)
      		pthread_mutex_init( &baguette[i], NULL);

   	for (i = 0; i < PHILOSOPHES; i++)
     		pthread_create(&phil[i], NULL, philosophe, (void*)&(id[i]) );

   	for (i = 0; i < PHILOSOPHES; i++)
      		pthread_join(phil[i], NULL);

   	return (EXIT_SUCCESS);
}





