#include "header.h"

void* lock_TS(int *arg){ //fonction test-set
	int y = 1;
	while(y!=0){
		asm (	"movl $1, %%eax;"	//mets 1 dans eax
  			"xchgl %%eax, (%1);"	//echange lock et eax	
       		"movl %%eax, %0;"	//mets la valeur de eax en sortie
    			:"=r"(y)  /* y is output operand */
    			:"r"(arg)   /* x is input operand */
   			:"%eax"); /* %eax is clobbered register */
	}
	//printf("lock valait 0, maintenant lock vaut %d et y vaut %d \n",*arg,y);	
}

void* lock_TTS(int *arg){ //fonction test-test-set
	int y = 1;
	while(y!=0){
		asm (	"movl $1, %%eax;"	//mets 1 dans eax
  			"xchgl %%eax, (%1);"	//echange lock et eax	
       		"movl %%eax, %0;"	//mets la valeur de eax en sortie
    			:"=r"(y)  /* y is output operand */
    			:"r"(arg)   /* x is input operand */
   			:"%eax"); /* %eax is clobbered register */
   			if(y==0){return NULL;}
   			while(*arg!=0);
	}
}

void* lock_BTTS(int *arg){ //fonction backoff-test-test-set
	int y = 1;
	int v = vmin;
	int wait;
	int x;
	while(y!=0){
		asm (	"movl $1, %%eax;"	//mets 1 dans eax
  			"xchgl %%eax, (%1);"	//echange lock et eax	
       		"movl %%eax, %0;"	//mets la valeur de eax en sortie
    			:"=r"(y)  /* y is output operand */
    			:"r"(arg)   /* x is input operand */
   			:"%eax"); /* %eax is clobbered register */
   			if(y==0){return NULL;}
   			v = vmin;
   			while(*arg!=0 || v*rand()>RAND_MAX/10000)if(v*2<vmax) v*=2;
	}
}

void* unlock(int *arg){ //fonction commune pour les 3 verrous
	asm (	"movl $0, %%eax;"	//mets 0 dans eax
  		"xchgl %%eax, (%0);"	//echange lock et eax	
  		:			//pas d'output
    		:"r"(arg)   /* x is input operand */
   		:"%eax"); /* %eax is clobbered register */
}

int* init(){ //fonction commune pour les 3 verrous
	int *arg = malloc(sizeof(int));
	*arg = 0;
	return arg;
}

void* destroy(int* arg){ //fonction commune pour les 3 verrous
	free(arg);
}

void* init_BTTS(int min, int max){ //choisir les intervalles d'attente entre les essais de lock_BTTS
	vmin = min;
	vmax = max;
}
