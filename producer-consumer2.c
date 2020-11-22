#include "header.h"
//gcc Producteurs-Consommateurs.c -o x -lpthread

// Productions
void* producer2(void* arg){
	int item;
	int my_id;
	empty2 = (semaphore*)arg;
	while(in<=1024){
		my_id = in;
		in++;
		item = rand();
		printf("CHECK 10\n");
		wait(empty2); //attente d'une place libre
		lock_TS(mutex_PC2);
		printf("CHECK 20\n");
		//selection critique
		if(my_id>1024){
			printf("CHECK 30\n");
			post(empty2); // une place libre en plus
			unlock(mutex_PC2);
			printf("CHECK 40\n");
			return NULL;
		}
		//printf("(%d) Producer %d: add item %d to %d\n",my_id,*((int*)arg),item,(my_id-1)%8);
		buffer[(my_id-1)%8] = item;
		while(rand()>RAND_MAX/10000);
		printf("CHECK 50\n");
		unlock(mutex_PC2);
		post(full2); // une place remplie en plus
		printf("CHECK 60\n");
	}
}

// Consommateur
void* consumer2(void* arg){
	printf("CHECK enter\n");
	int item;
	int my_id;
	full2 = (semaphore*)arg;
	while(out<=1024){
		my_id = out;
		out++;
		printf("CHECK 70\n");
		wait(full2); // attente d'une place remplie
		lock_TS(mutex_PC2);
		printf("CHECK 80\n");
		// selection critique
		if(my_id>1024){
			printf("CHECK 90\n");
			post(full2); // une place remplie en plus
			unlock(mutex_PC2);
			printf("CHECK 100\n");
			return NULL;
		}
		item = buffer[(my_id-1)%8];
		buffer[(my_id-1)%8]=0;
		//printf("(%d) Consumer %d: remove item %d from %d\n",my_id,*((int*)arg),item,(my_id-1)%8);
		while(rand()>RAND_MAX/10000);
		printf("CHECK 110\n");
		unlock(mutex_PC2);
		post(empty2); // une place libre en plus
		printf("CHECK 120\n");
		if(my_id==1024){
			printf("CHECK 130\n");
			post(full2); // une place remplie en plus (fake)
			printf("CHECK 140\n");
			
		}
	}
}
	
int main_PC2(int producers, int consumers){
	
	if(producers==0 || consumers==0){
		return(EXIT_SUCCESS);
	}
	
	pthread_t prod[producers];
	pthread_t cons[consumers];
	in = 1;
	out = 1;

	long i;
	int idP[producers];
	int idC[consumers];

	mutex_PC2 = init();
	semaphore* empty2 = init_S(8, 8);
	semaphore* full2 = init_S(0, 8);

	srand(getpid());
	
	for(i=0; i<producers; i++){
		idP[i]=i+1;
	}
	for(i=0; i<consumers; i++){
		idC[i]=i+1;
	}
	for(i=0; i<producers; i++){
		pthread_create(&prod[i], NULL, producer2, (void*)empty2);//&(idP[i])
	}
	for(i=0; i<consumers; i++){
		pthread_create(&cons[i], NULL, consumer2, (void*)full2);//&(idC[i])
	}
	for(i=0; i<producers; i++){
		printf("CHECK 1\n");
		pthread_join(prod[i], NULL);
	}
	for(i=0; i<consumers; i++){
		printf("CHECK 2\n");
		pthread_join(cons[i], NULL);
	}
	printf("CHECK 3\n");
	destroy(mutex_PC2);
	while(rand()>RAND_MAX/10000);
	printf("CHECK 4\n");
	destroy_S(empty2);
	while(rand()>RAND_MAX/10000);
	printf("CHECK 5\n");
	destroy_S(full2);
	return(EXIT_SUCCESS);
}
