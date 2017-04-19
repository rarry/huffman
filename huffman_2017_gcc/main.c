#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "huffman.h"
#include "priorityQueue.h"
#include "crc.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	int i;
//	char * inFp = "testFiles/great/great.txt";
//	char * inFpCrc = "testFiles/great/great_crc.txt";
//	char * codedFp = "testFiles/great/great_compressed.txt";
//	char * decodedFpCrc = "testFiles/great/great_decompressed_crc.txt";
//	char * decodedFp = "testFiles/great/great_decompressed.txt";

//	char * inFp = "testFiles/abc/abc.txt";
//	char * inFpCrc = "testFiles/abc/abc_crc.txt";
//	char * codedFp = "testFiles/abc/abc_compressed.txt";
//	char * decodedFpCrc = "testFiles/abc/abc_decompressed_crc.txt";
//	char * decodedFp = "testFiles/abc/abc_decompressed.txt";

	char * inFp = "testFiles/a/a.txt";
	char * inFpCrc = "testFiles/a/a_crc.txt";
	char * codedFp = "testFiles/a/a_compressed.txt";
	char * decodedFpCrc = "testFiles/a/a_decompressed_crc.txt";
	char * decodedFp = "testFiles/a/a_decompressed.txt";

	int freq[LETTERS_COUNT];
	struct NODE *heap[LETTERS_COUNT+1];
	unsigned long int codeTable[LETTERS_COUNT];
	int heapSize = 1;

	copyFile(inFp, inFpCrc);

    unsigned char * restPoly = calculateCrc(inFp);
    printf("Generated polynomial:\n");
    printPolynomial(restPoly, SIZECRC);

    appendCrcToFile(inFpCrc, SIZECRC, restPoly);

	// calculate frequencies of letters in an input file
	calculateFreq(inFpCrc, freq);
	//printFrequencies(freq, LETTERS_COUNT);

	// build heap (priority queue)
	for(i=0; i<LETTERS_COUNT; i++){
        struct NODE *node = malloc(sizeof(struct NODE));
		node->letterIndex = i;
		node->left = NULL;
		node->right = NULL;
		node->weight = freq[i];

		insert(heap, heapSize, node);
		heapSize++;
	}

    struct NODE *root = buildHuffmanTree(heap, heapSize);
    //printHuffmanTreeBfs(root);
//
    fillCodeTable(codeTable, root);
//
    //printf("Printing code table\n");
    //printCodeTable(codeTable, LETTERS_COUNT);
//
    compressFile(inFpCrc, codedFp, codeTable);
//
    decompressFile(codedFp, decodedFpCrc, root);

    unsigned char * restPolyFromDec = calculateCrc(decodedFpCrc);
    printf("\n\nRest from decopressed file:\n");
    printPolynomial(restPolyFromDec, SIZECRC);

    if(!isIntegral(restPolyFromDec, SIZECRC)){
        printf("Integrity check failed!\n\n");
        exit(EXIT_FAILURE);
    }else{
        printf("Integrity check passed!\n\n");
        copySkip(decodedFpCrc, decodedFp, SIZECRC);
    }

	return 0;
}
