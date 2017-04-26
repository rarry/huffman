#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void printFrequencies(int freq[], int length){

	int i;
    for(i=0; i<length; i++)
    {
        printf("%d ", freq[i]);
    }
    printf("\n");
}



