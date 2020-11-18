#include "header.h"
//gcc header.h reader-writer.c philosophers.c producer-consumer.c main.c -o x -lpthread

int main(int argc, char const *argv[]){
	if(strcmp(argv[1], "-PC")==0){
		main_PC(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-RW")==0){
		main_RW(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-P")==0){
		main_P(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "-TS")==0){
		main_TS();
	}
	else{printf("Wrong argument\n");}
}
