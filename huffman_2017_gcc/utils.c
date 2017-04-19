#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "huffman.h"

void printFrequencies(int freq[], int length){

	int i;
    for(i=0; i<length; i++)
    {
        printf("%d ", freq[i]);
    }
    printf("\n");
}

void printNodes(struct NODE *nodes[], int length){

	int i;
    for(i=0; i<length; i++)
    {
        printf("(%d -> %d)\t", i, nodes[i]->weight);
    }
    printf("\n");
}

void printHeapArray(struct NODE *nodes[], int length){
    int i;
    for(i=1; i<length; i++)
    {
        printf("(%d -> %d)\t", i, nodes[i]->weight);
    }
    printf("\n");
}


void resetTab(struct NODE *nodes[], int length){

    int i;
    for(i=0; i<length; i++)
    {
        nodes[i]->letterIndex = 0;
        nodes[i]->weight = 0;
    }
    printf("\n");
}

void copyFile(char *from, char *to)
{
    FILE * input;
    FILE * output;

    if((input = fopen(from, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(to, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    int c;
    do
    {
        c = fgetc(input);
        if( feof(input) )
        {
            break ;
        }
        fputc(c, output);
    }while(1);

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void printPolynomial(unsigned char * restPolynomial, int size)
{
    int i;
    for(i=0; i<size; i++)
    {
        printf("Bajt %d wartosci CRC: %#x\n", i, restPolynomial[i]);
    }
}

void copySkip(char * inputName, char * outputName, int skipBytes)
{

    FILE * input;
    FILE * output;

    if((input = fopen(inputName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }


    fseek(input, 0L, SEEK_END);
    int fileSize = ftell(input);
    rewind(input);

    int c;
    int i;

    for(i=0; i<fileSize-skipBytes; i++)
    {
        c = fgetc(input);
        fputc(c, output);
    }

    if(fclose(input) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    if(fclose(output) != NULL)
    {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}



