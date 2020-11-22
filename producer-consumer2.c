#include "header.h"
//gcc Producteurs-Consommateurs.c -o x -lpthread

// Productions
void* producer2(void* arg){
	int item;
	int my_id;
	while(in<=1024){
		my_id = in;
		in++;
		item = rand();
		wait(empty2); //attente d'une place libre
		lock_TS(mutex_PC2);
		//selection critique
		if(my_id>1024){
			post(empty2); // une place libre en plus // b producer-consumer2.c:17
			unlock(mutex_PC2);
			return NULL;
		}
		buffer[(my_id-1)%8] = item;
		while(rand()>RAND_MAX/10000);
		unlock(mutex_PC2);
		post(full2); // une place remplie en plus // b producer-consumer2.c:24
	}
}

// Consommateur
void* consumer2(void* arg){
	int item;
	int my_id;
	while(out<=1024){
		my_id = out;
		out++;
		wait(full2); // attente d'une place remplie
		lock_TS(mutex_PC2);
		// selection critique
		if(my_id>1024){
			post(full2); // une place remplie en plus // b producer-consumer2.c:40
			unlock(mutex_PC2);
			return NULL;
		}
		item = buffer[(my_id-1)%8];
		buffer[(my_id-1)%8]=0;
		while(rand()>RAND_MAX/10000);
		unlock(mutex_PC2);
		post(empty2); // une place libre en plus // b producer-consumer2.c:48
		if(my_id==1024){
			post(full2); // une place remplie en plus (fake) // b producer-consumer2.c:50
			
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
	empty2 = init_S(8, 8);
	full2 = init_S(0, 8);

	srand(getpid());
	
	for(i=0; i<producers; i++){
		idP[i]=i+1;
	}
	for(i=0; i<consumers; i++){
		idC[i]=i+1;
	}
	for(i=0; i<producers; i++){
		pthread_create(&prod[i], NULL, producer2, (void*)&(idP[i]));//&(idP[i])
	}
	for(i=0; i<consumers; i++){
		pthread_create(&cons[i], NULL, consumer2, (void*)&(idC[i]));//&(idC[i])
	}
	for(i=0; i<producers; i++){
		pthread_join(prod[i], NULL);
	}
	for(i=0; i<consumers; i++){
		pthread_join(cons[i], NULL);
	}
	destroy(mutex_PC2); // b producer-consumer2.c:95
	destroy_S(empty2);
	destroy_S(full2);
	return(EXIT_SUCCESS);
}
