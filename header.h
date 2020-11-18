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

#define N 10 // places dans le buffer

// variables globales de RW
int number_of_write;
int number_of_read;
pthread_mutex_t mutex_RW;
pthread_mutex_t z;
pthread_mutex_t m_w;
sem_t db;  // accès à la db
sem_t rsem;
int readcount; // nombre de readers en train de lire
int w;	//nombre d'écrivains en train d'écrire

// variables globales de PC
pthread_mutex_t mutex_PC;
sem_t empty;
sem_t full;
int buffer[8];
int in;
int out;

// variables globales de P
pthread_mutex_t *baguette;
int philosophess;

//variables globales de TS
long lockk;

//Fonctions RW
void* writer(void* arg);
void* reader(void* arg);
int main_RW(int writers, int readers);

//Fonctions PC
void* producer(void* arg);
void* consumer(void* arg);
int main_PC(int producers, int consumers);

//Fonctions P
void* philosophe ( void* arg );
int main_P(int philosophes);

//Fonctions TS
int lock(long lock);
int unlock(long lock);
int main_TS();

#endif
