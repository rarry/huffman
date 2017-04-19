#ifndef PQ_H_INCLUDED
#define PQ_H_INCLUDED

#include "huffman.h"

void swim(struct NODE *nodes[], int index);

void insert(struct NODE *nodes[], int n, struct NODE *node);

void sink(struct NODE *nodes[], int n, int index);

struct NODE * delMin(struct NODE *nodes[], int heapSize);

int compare(struct NODE *a, struct NODE *b);

void exch(struct NODE *nodes[], int a, int b);

#endif
