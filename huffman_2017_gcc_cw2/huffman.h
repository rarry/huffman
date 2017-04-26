#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED

#define LETTERS_COUNT   255
#define MAX_WORD_LENGTH   100

struct NODE {
	int letterIndex;
	struct NODE *left, *right;
	int weight;
};

struct CODE_WORD {
    int length;
    unsigned char *word;
};

struct NODE * buildHuffmanTree(struct NODE *heap[], int heapSize);

void printHuffmanTreeBfs(struct NODE *root);

void fillCodeTable(unsigned long int codeTable[], struct NODE *node);

void printCodeTable(unsigned long int codeTable[], int length);

void compressFile(char *inputFileName, char * outputFileName, unsigned long int codeTable[]);

void decompressFile(char *inputFileName, char * outputFileName, struct NODE *root);

#endif
