#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "header.h"

//variables globales de TS
int* mutex_TS;
int nbthread_TS;

//variables globales de TTS
int* mutex_TTS;
int nbthread_TTS;

//variables globales de BTTS
int* mutex_BTTS;
int nbthread_BTTS;
int vmin;
int vmax;

//variables globales de sem
int nmax;
int ncurrent;
typedef struct def{
	int current;
	int max;
	int index;
	int **mutex;
	int* sem_mutex;
}semaphore;

// variables globales de RW & RW2
int number_of_write;
int number_of_read;
pthread_mutex_t mutex_RW;
pthread_mutex_t z;
pthread_mutex_t m_w;
int* mutex_RW2;
int* z2;
int* m_w2;
sem_t db;  // accès à la db
sem_t rsem;
semaphore* db2;
semaphore* rsem2;
int readcount; // nombre de readers en train de lire
int w;	//nombre d'écrivains en train d'écrire

// variables globales de PC & PC2
pthread_mutex_t mutex_PC;
int* mutex_PC2;
sem_t empty;
sem_t full;
semaphore* empty2;
semaphore* full2;
int buffer[8];
int in;
int out;

// variables globales de P & P2
pthread_mutex_t *baguette;
int **baguette2;
int philosophess;

//Fonctions RW
void* writer(void* arg);
void* reader(void* arg);
int main_RW(int writers, int readers);

//Fonctions PC
void* producer(void* arg);
void* consumer(void* arg);
int main_PC(int producers, int consumers);

//Fonctions P
void* philosophe(void* arg);
int main_P(int philosophes);

//Fonctions RW2
void* writer2(void* arg);
void* reader2(void* arg);
int main_RW2(int writers, int readers);

//Fonctions PC2
void* producer2(void* arg);
void* consumer2(void* arg);
int main_PC2(int producers, int consumers);

//Fonctions P2
void* philosophe2(void* arg);
int main_P2(int philosophes);

//Fonctions verrou
void* lock_TS(int *arg);
void* lock_TTS(int *arg);
void* lock_BTTS(int *arg);
void* unlock(int *arg);
int* init();
void* destroy(int *arg);

//Fonctions TS
void* test_TS(void *arg);
int main_TS(int n);

//Fonctions TTS
void* test_TTS(void *arg);
int main_TTS(int n);

//Fonctions BTTS
void* test_BTTS(void *arg);
int main_BTTS(int n, int min, int max);
void* init_BTTS(int min, int max);

//Fonctions sem
void* post(semaphore *arg);
void* wait(semaphore *arg);
semaphore* init_S(int start, int maxi);
void* destroy_S(semaphore* arg);
#endif
