#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "huffman.h"
#include "priorityQueue.h"
#include "crc.h"

int main(int argc, char *argv[]) {

	int i;
//	char * inFp = "C:\\test_huffman\\great\\great.txt";
//	char * inFpCrc = "C:\\test_huffman\\great\\great_crc.txt";
//	char * codedFp = "C:\\test_huffman\\great\\great_compressed.txt";
//	char * decodedFpCrc = "C:\\test_huffman\\great\\great_decompressed_crc.txt";
//	char * decodedFp = "C:\\test_huffman\\great\\great_decompressed.txt";

//    char * inFp = "C:\\test_huffman\\abc.txt";
//	char * inFpCrc = "C:\\test_huffman\\abc_crc.txt";
//	char * codedFp = "C:\\test_huffman\\abc_compressed.txt";
//	char * decodedFpCrc = "C:\\test_huffman\\abc_decompressed_crc.txt";
//	char * decodedFp = "C:\\test_huffman\\abc_decompressed.txt";

    char * inFp = "C:\\test_huffman\\a\\a.txt";
	char * inFpCrc = "C:\\test_huffman\\a\\a_crc.txt";
	char * codedFp = "C:\\test_huffman\\a\\a_compressed.txt";
	char * decodedFpCrc = "C:\\test_huffman\\a\\a_decompressed_crc.txt";
	char * decodedFp = "C:\\test_huffman\\a\\a_decompressed.txt";

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

    if(!isIntegral()){
        printf("Integrity check failed!");
        exit(EXIT_FAILURE);
    }else{
        printf("Integrity check passed!\n\n");
        copySkip(decodedFpCrc, decodedFp, SIZECRC);
    }

	return 0;
}
