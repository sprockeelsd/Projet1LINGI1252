#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
//gcc Producteurs-Consommateurs.c -o x -lpthread

// Initialisation
#define N 10 // places dans le buffer
#define PRODUCERS 3 // nombre de PRODUCERS
#define CONSUMERS 1 // nombre de CONSUMERS

pthread_t prod[PRODUCERS];
pthread_t cons[CONSUMERS];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int buffer[8];
int in = 0;
int out = 0;

// Productions
void* producer(void* arg){
	int item;
	while(in<1024){
		item = rand();
		sem_wait(&empty); //attente d'une place libre
		pthread_mutex_lock(&mutex);
		//selection critique
		if(in==1024){
			pthread_mutex_unlock(&mutex);
			return NULL;
		}
		//printf("(%d) Producer %d: add item %d to %d\n",in+1,*((int*)arg),item,in%8);
		buffer[in%8] = item;
		in++;
		//if(in==1024){printf("(%d) Producer %d: add item %d to %d\n",in,*((int*)arg),item,in%8);}
		while(rand()>RAND_MAX/10000);
		pthread_mutex_unlock(&mutex);
		sem_post(&full); // une place remplie en plus
	}
}

// Consommateur
void* consumer(void* arg){
	int item;
	while(out<1024){
		sem_wait(&full); // attente d'une place remplie
		pthread_mutex_lock(&mutex);
		// selection critique
		item = buffer[out%8];
		//printf("(%d) Consumer %d: remove item %d from %d\n",out+1,*((int*)arg),item,out%8);
		out++;
		while(rand()>RAND_MAX/10000);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty); // une place libre en plus
	}
	printf("(%d) Consumer %d: remove item %d from %d\n",out,*((int*)arg),item,out%8);
}
	
int main() {
	long i;
	int idP[PRODUCERS];
	int idC[CONSUMERS];

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, 8); // buffer vide
	sem_init(&full, 0, 0); // buffer full
	
	srand(getpid());
	
	for(i=0; i<PRODUCERS; i++){
		idP[i]=i+1;
	}
	for(i=0; i<CONSUMERS; i++){
		idC[i]=i+1;
	}
	for(i=0; i<PRODUCERS; i++){
		pthread_create(&prod[i], NULL, producer, (void*)&(idP[i]));
	}
	for(i=0; i<CONSUMERS; i++){
		pthread_create(&cons[i], NULL, consumer, (void*)&(idC[i]));
	}
	for(i=0; i<PRODUCERS; i++){
		pthread_join(prod[i], NULL);
	}
	for(i=0; i<CONSUMERS; i++){
		pthread_join(cons[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return(EXIT_SUCCESS);
}
