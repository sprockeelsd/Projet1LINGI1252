#include "header.h"
//gcc -o reader-writer reader-writer.c -lpthread

void* writer(void* arg){
    while(number_of_write < 640){
    	//simule la préparation des données à écrire
        pthread_mutex_lock(&m_w);
        w++;
        if(w == 1)
        {
   	        sem_wait(&rsem);
        }
        pthread_mutex_unlock(&m_w);
        sem_wait(&db);
        if(number_of_write == 640){
        	sem_post(&db);
        	w--;
        	if(w == 0){
        		sem_post(&rsem);
        	}
        	return NULL;
        }
        while(rand() > RAND_MAX/10000);
        //printf("le thread %d a fait la %d ème écriture \n",*((int*)arg),number_of_write);
      	number_of_write++;
        
        sem_post(&db);
        pthread_mutex_lock(&m_w);
        w--;
        if (w == 0)
        {
   	        sem_post(&rsem);
        }
        pthread_mutex_unlock(&m_w);
    }
    //printf("number of writes : %d \n",number_of_write);
}

void* reader(void* arg){
    while(number_of_read < 2560){
        pthread_mutex_lock(&z);
        sem_wait(&rsem);
        pthread_mutex_lock(&mutex_RW);
        // section critique
        if(number_of_read >= 2560- readcount){
         	pthread_mutex_unlock(&mutex_RW);
         	sem_post(&rsem);
        	pthread_mutex_unlock(&z);
        	return NULL;
        }
        readcount++;
        if (readcount==1){ // arrivée du premier reader
            sem_wait(&db);
        }
        
        pthread_mutex_unlock(&mutex_RW);
        sem_post(&rsem);
        pthread_mutex_unlock(&z);
        while(rand() > RAND_MAX/10000);
        //printf("le thread %d a fait la %d ème écriture \n",*((int*)arg),number_of_read);
        number_of_read++;
        
        pthread_mutex_lock(&mutex_RW);
        // section critique
        readcount--;
        if(readcount==0){ // départ du dernier reader
            sem_post(&db);
        }
        pthread_mutex_unlock(&mutex_RW);
    }
    //printf("number of read : %d \n",number_of_read);
}

int main_RW(int writers, int readers){
	
	//nombre de read et write actuels, pour compter quand on arrive à la limite
	number_of_write = 0;
	number_of_read = 0;

	pthread_t ecrivains[writers];
	pthread_t lecteurs[readers];

	readcount=0; // nombre de readers en train de lire
	w = 0;	//nombre d'écrivains en train d'écrire

	long i;
	int Wid[writers];
	int Rid[readers];
	
	sem_init(&rsem, 0, 1);
	sem_init(&db, 0, 1);
	pthread_mutex_init(&mutex_RW, NULL);
	pthread_mutex_init(&z, NULL);
	pthread_mutex_init(&m_w, NULL);
	
	
	srand(getpid());
	
	for(i=0; i<writers; i++){
		Wid[i]=i+1;
	}
	for(i=0; i<readers; i++){
		Rid[i]=i+1;
	}
	for(i=0; i<writers; i++){
		pthread_create(&ecrivains[i], NULL, writer, (void*)&(Wid[i]));
	}
	for(i=0; i<readers; i++){
		pthread_create(&lecteurs[i], NULL, reader, (void*)&(Rid[i]));
	}
	for(i=0; i<writers; i++){
		pthread_join(ecrivains[i], NULL);
	}
	for(i=0; i<readers; i++){
		pthread_join(lecteurs[i], NULL);
	}
	sem_destroy(&rsem);
	sem_destroy(&db);
	pthread_mutex_destroy(&mutex_RW);
	pthread_mutex_destroy(&z);
	pthread_mutex_destroy(&m_w);
}
