#include "header.h"
//gcc Producteurs-Consommateurs.c -o x -lpthread

// Productions
void* producer(void* arg){
	int item;
	int my_id;
	while(in<=24){
		my_id = in;
		in++;
		item = rand();
		sem_wait(&empty); //attente d'une place libre
		pthread_mutex_lock(&mutex_PC);
		//selection critique
		if(my_id>24){
			sem_post(&empty); // une place libre en plus
			pthread_mutex_unlock(&mutex_PC);
			return NULL;
		}
		//printf("(%d) Producer %d: add item %d to %d\n",my_id,*((int*)arg),item,(my_id-1)%8);
		buffer[(my_id-1)%8] = item;
		while(rand()>RAND_MAX/10000);
		pthread_mutex_unlock(&mutex_PC);
		sem_post(&full); // une place remplie en plus
	}
}

// Consommateur
void* consumer(void* arg){
	int item;
	int my_id;
	while(out<=24){
		my_id = out;
		out++;
		sem_wait(&full); // attente d'une place remplie
		pthread_mutex_lock(&mutex_PC);
		// selection critique
		if(my_id>24){
			sem_post(&full); // une place remplie en plus
			pthread_mutex_unlock(&mutex_PC);
			return NULL;
		}
		item = buffer[(my_id-1)%8];
		buffer[(my_id-1)%8]=0;
		//printf("(%d) Consumer %d: remove item %d from %d\n",my_id,*((int*)arg),item,(my_id-1)%8);
		while(rand()>RAND_MAX/10000);
		pthread_mutex_unlock(&mutex_PC);
		sem_post(&empty); // une place libre en plus
		if(my_id==24){
			sem_post(&full); // une place remplie en plus (fake)
			
		}
	}
}
	
int main_PC(int producers, int consumers){
	
	pthread_t prod[producers];
	pthread_t cons[consumers];
	in = 1;
	out = 1;

	long i;
	int idP[producers];
	int idC[consumers];

	pthread_mutex_init(&mutex_PC, NULL);
	sem_init(&empty, 0, 8); // buffer vide
	sem_init(&full, 0, 0); // buffer full
	
	srand(getpid());
	
	for(i=0; i<producers; i++){
		idP[i]=i+1;
	}
	for(i=0; i<consumers; i++){
		idC[i]=i+1;
	}
	for(i=0; i<producers; i++){
		pthread_create(&prod[i], NULL, producer, (void*)&(idP[i]));
	}
	for(i=0; i<consumers; i++){
		pthread_create(&cons[i], NULL, consumer, (void*)&(idC[i]));
	}
	for(i=0; i<producers; i++){
		pthread_join(prod[i], NULL);
	}
	for(i=0; i<consumers; i++){
		pthread_join(cons[i], NULL);
	}
	pthread_mutex_destroy(&mutex_PC);
	sem_destroy(&empty);
	sem_destroy(&full);
	return(EXIT_SUCCESS);
}
