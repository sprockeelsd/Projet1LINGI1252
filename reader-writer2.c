#include "header.h"
//gcc -o reader-writer reader-writer.c -lpthread

void* writer2(void* arg){
    while(number_of_write < 640){
    	//simule la préparation des données à écrire
        lock_TS(m_w2);
        w++;
        if(w == 1)
        {
   	        wait(rsem2);
        }
        unlock(m_w2);
        wait(db2);
        if(number_of_write == 640){
        	post(db2);
        	w--;
        	if(w == 0){
        		post(rsem2);
        	}
        	return NULL;
        }
        while(rand() > RAND_MAX/10000);
        //printf("le thread %d a fait la %d ème écriture \n",*((int*)arg),number_of_write);
      	number_of_write++;
        
        post(db2);
        lock_TS(m_w2);
        w--;
        if (w == 0)
        {
   	        post(rsem2);
        }
        unlock(m_w2);
    }
    //printf("number of writes : %d \n",number_of_write);
}

void* reader2(void* arg){
    while(number_of_read < 2560){
        lock_TS(z2);
        wait(rsem2);
        lock_TS(mutex_RW2);
        // section critique
        if(number_of_read >= 2560- readcount){
         	unlock(mutex_RW2);
         	post(rsem2);
        	unlock(z2);
        	return NULL;
        }
        readcount++;
        if (readcount==1){ // arrivée du premier reader
            wait(db2);
        }
        
        unlock(mutex_RW2);
        post(rsem2);
        unlock(z2);
        while(rand() > RAND_MAX/10000);
        //printf("le thread %d a fait la %d ème écriture \n",*((int*)arg),number_of_read);
        number_of_read++;
        
        lock_TS(mutex_RW2);
        // section critique
        readcount--;
        if(readcount==0){ // départ du dernier reader
            post(db2);
        }
        unlock(mutex_RW2);
    }
    //printf("number of read : %d \n",number_of_read);
}

int main_RW2(int writers, int readers){
	
	if(writers==0 || readers==0){
		return(EXIT_SUCCESS);
	}
	
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
	
	rsem2 = init_S(1,1);
	db2 = init_S(1,1);

	mutex_RW2 = init();
	z2 = init();
	m_w2 = init();
	
	srand(getpid());
	
	for(i=0; i<writers; i++){
		Wid[i]=i+1;
	}
	for(i=0; i<readers; i++){
		Rid[i]=i+1;
	}
	for(i=0; i<writers; i++){
		pthread_create(&ecrivains[i], NULL, writer2, (void*)&(Wid[i]));
	}
	for(i=0; i<readers; i++){
		pthread_create(&lecteurs[i], NULL, reader2, (void*)&(Rid[i]));
	}
	for(i=0; i<writers; i++){
		pthread_join(ecrivains[i], NULL);
	}
	for(i=0; i<readers; i++){
		pthread_join(lecteurs[i], NULL);
	}
	destroy_S(rsem2);
	destroy_S(db2);
	destroy(mutex_RW2);
	destroy(z2);
	destroy(m_w2);
}
