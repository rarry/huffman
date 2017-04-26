#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "utils.h"

#define LETTERS_COUNT   255

int main(int argc, char *argv[]) {

	char * inFp = "C:\\test_huffman\\a\\a.txt";

	int freq[LETTERS_COUNT];

	// calculate frequencies of letters in an input file
	calculateFreq(inFp, freq, LETTERS_COUNT);
	printFrequencies(freq, LETTERS_COUNT);

	return 0;
}
