#include "header.h"

void* lock(int *arg){
	int y = 1;
	int n = 0;
	while(y!=0 && n < 5){
		asm (	"movl $1, %%eax;"	//mets 1 dans eax
  			"xchgl %%eax, (%1);"	//echange lock et eax	
       		"movl %%eax, %0;"	//mets la valeur de eax en sortie
    			:"=r"(y)  /* y is output operand */
    			:"r"(arg)   /* x is input operand */
   			:"%eax"); /* %eax is clobbered register */
   			printf("%d\n",y);
   			printf("arg = %d\n",*arg);
   			n++;
	}
	printf("lock valait 0, maintenant lock vaut %d et y vaut %d \n",*arg,y);
	
}

void* unlock(int *arg){
	asm (	"movl $0, %%eax;"	//mets 0 dans eax
  		"xchgl %%eax, (%0);"	//echange lock et eax	
  		:			//pas d'output
    		:"r"(arg)   /* x is input operand */
   		:"%eax"); /* %eax is clobbered register */
}

void* init_TS(int *arg){
	arg = malloc(sizeof(int));
	*arg = 0;
}

void* destroy(int* arg){
	free(arg);
}








