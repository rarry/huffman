#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "huffman.h"
#include "priorityQueue.h"

#define len(x) ((int)log2(x)+1)



struct NODE * buildHuffmanTree(struct NODE heap[], int heapSize){

    struct NODE *newParent;
    while(heapSize > 2){
        //printHeapArray(heap, heapSize);
        struct NODE *smallest = delMin(heap, heapSize);
        heapSize--;
        struct NODE *secondSmallest = delMin(heap, heapSize);
        heapSize--;

        //printf("Merging: (%d, %d) into %d, heap size: %d\n", smallest->weight, secondSmallest->weight, smallest->weight + secondSmallest->weight, heapSize);

        newParent = (struct NODE *) malloc(sizeof(struct NODE));

        newParent->letterIndex = -1;
        newParent->left = smallest;
        newParent->right = secondSmallest;
        newParent->weight = smallest->weight + secondSmallest->weight;

        //printHuffmanTreeBfs(newParent);
        insert(heap, heapSize, newParent);

        heapSize++;

    }

    struct NODE *min = delMin(heap, heapSize);
    //printHuffmanTreeBfs(&min);
    return min;
};

void printInner(struct NODE *node){
    if(node){
        printf("%d\n", node->weight);
        printInner(node->left);
        printInner(node->right);
    }
}

void printBinary(struct NODE *node){
    if(node->left){
        printf("going left\t");
        printBinary(node->left);
    }

    if(node->right){
        printf("going right\t");
        printBinary(node->right);
    }
    printf("\n");

}


void printHuffmanTreeBfs(struct NODE *node){
    printInner(node);
}

unsigned char isLeaf(struct NODE *node){
    if(node && !(node->left) && !(node->right)){
        return 1;
    }else{
        return 0;
    }
}

void copy(unsigned char *to, unsigned char *from, int size){
    int i;
    for(i=0; i<size; i++){
        to[i] = from[i];
    }
}

void fillCodeTableInner(unsigned long int codeTable[], unsigned long int codeWord, struct NODE *node){
    if(node){

        if(isLeaf(node)){
            int index = node->letterIndex;
            codeTable[index] = codeWord;
        }else{
            //printf("%d\n", node->weight);
            if(node->left){
                unsigned long int newWord = codeWord << 1;
                fillCodeTableInner(codeTable, newWord, node->left);
            }
            if(node->right){
                unsigned long int newWord = codeWord << 1;
                newWord = newWord | 1;
                fillCodeTableInner(codeTable, newWord, node->right);
            }
        }
    }
}

void fillCodeTable(unsigned long int codeTable[], struct NODE *node){
    fillCodeTableInner(codeTable, 1, node);
}

void printCodeWord(unsigned long int n){
    int c;
    unsigned long int k;
    char leadingZeroes = 1;

    for (c = 31; c >= 0; c--){
        k = n >> c;

        if (k & 1){
          printf("1");
          leadingZeroes = 0;
        }else if(!leadingZeroes){
          printf("0");
        }
      }
}

void printCodeTable(unsigned long int codeTable[], int length){
    int i;
    for(i=1; i<length; i++){
        printf("codeTable[%d] -> %lu:\t", i, codeTable[i]);
        printCodeWord(codeTable[i]);
        printf("\n");
    }
}

int getBit(int c, int bitIndex, int length){

    int mask = pow(2, length-1-bitIndex);
    int v = c & mask;
    if(v > 0){
        return 1;
    }else{
        return 0;
    }
}

void compress(FILE *input, FILE *output, unsigned long int codeTable[]){

    int ch;
    int chunk = 0;
    int chunkSize = 0;

    while((ch = fgetc(input)) != EOF){

        unsigned long int c = codeTable[ch];
        int cSize = len(c);

        int bitIndex;
        for(bitIndex=0; bitIndex<cSize; bitIndex++){
            int bit = getBit(c, bitIndex, cSize);

            chunk = chunk << 1;
            chunk = chunk | bit;
            chunkSize++;

            if(chunkSize == 8){
                fputc(chunk, output);
                chunk = 0;
                chunkSize = 0;
            }
        }
    }

    if(chunkSize >0){
        chunk = chunk << 8-chunkSize;
        fputc(chunk, output);
    }
}

void compressFile(char *inputFileName, char * outputFileName, unsigned long int codeTable[])
{

    FILE * input;
    FILE * output;

    if((input = fopen(inputFileName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputFileName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    compress(input, output, codeTable);

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

void decompress(FILE * input, FILE * output, struct NODE *root){

    struct NODE *node = root;
    int c;
    int skipNext = 1;

    while((c = fgetc(input)) != EOF){
        int i;
        for(i=0; i<8; i++){
            if(skipNext){
                skipNext = 0;
                continue;
            }
            int bit = getBit(c, i, 8);

            if(bit == 0){
                node = node->left;
            }else{
                node = node->right;
            }

            if(isLeaf(node)){
                int index = node->letterIndex;
                int w = index;
                fputc(w, output);
                node = root;
                skipNext = 1;
            }
        }
    }
}

void decompressFile(char *inputFileName, char * outputFileName, struct NODE *root)
{
    FILE * input;
    FILE * output;

    if((input = fopen(inputFileName, "rb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    if((output = fopen(outputFileName, "wb")) == NULL)
    {
        perror("Nie mozna otworzyc pliku");
        exit(EXIT_FAILURE);
    }

    decompress(input, output, root);

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
