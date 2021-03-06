#include "header.h"
//gcc header.h reader-writer.c philosophers.c producer-consumer.c main.c -o x -lpthread

//Le code qui redistribue les appels aux bonnes fonctions avec les bon arguments
int main(int argc, char const *argv[]){
	if(argc<3) return(EXIT_SUCCESS);
	else if(strcmp(argv[1], "-PC")==0){
		main_PC(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-RW")==0){
		main_RW(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-P")==0){
		main_P(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "-PC2")==0){
		main_PC2(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-RW2")==0){
		main_RW2(atoi(argv[2]),atoi(argv[3]));
	}
	else if(strcmp(argv[1], "-P2")==0){
		main_P2(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "-TS")==0){
		main_TS(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "-TTS")==0){
		main_TTS(atoi(argv[2]));
	}
	else if(strcmp(argv[1], "-BTTS")==0){
		main_BTTS(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
	}
	else{printf("Wrong argument\n");}
	return(EXIT_SUCCESS);
}
