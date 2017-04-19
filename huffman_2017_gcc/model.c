#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "model.h"
#include "utils.h"


void calculateFreq(char *inputFile, int freq[]){

	int i;
	for(i=0; i<LETTERS_COUNT; i++){
		freq[i] = 0;
	}

	FILE *f;

	f = fopen(inputFile, "r");

	if(f == NULL){
		perror("Cannot open file");
		exit(EXIT_FAILURE);
	}

	int ch;
	while((ch = fgetc(f)) != EOF){
        freq[ch] ++;
	}

	if(fclose(f) != 0){
		perror("Cannot close file");
		exit(EXIT_FAILURE);
	}

}
