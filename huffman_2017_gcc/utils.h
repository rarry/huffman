#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "huffman.h"

void printFrequencies(int freq[], int length);

void printNodes(struct NODE *nodes[], int length);

void printHeap(struct NODE *nodes[], int length);

void resetTab(struct NODE *nodes[], int length);

void copyFile(char *from, char *to);

void printPolynomial(unsigned char * restPolynomial, int size);

void copySkip(char * inputName, char * outputName, int skipBytes);

#endif
