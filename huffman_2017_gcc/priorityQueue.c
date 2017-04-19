#include<stdio.h>
#include "huffman.h"
#include "priorityQueue.h"

void swim(struct NODE *nodes[], int index){
	int k=index;
	struct NODE *parent = nodes[k/2];
	struct NODE *thisNode = nodes[k];
	while(k > 1 && compare(parent, thisNode) < 0) {
		exch(nodes, k, k/2);
		k = k / 2;
		parent = nodes[k/2];
        thisNode = nodes[k];
	}
}

void insert(struct NODE *nodes[], int heapSize, struct NODE *node){

	nodes[heapSize] = node;
	swim(nodes, heapSize);
}

void sink(struct NODE *nodes[], int heapSize, int k){

	while(2*k < heapSize){
		int j = 2*k;
		if(j < heapSize - 1 && compare(nodes[j], nodes[j+1]) < 0){
            j++;
		}
		if(compare(nodes[k], nodes[j])>0) break;
		exch(nodes, k, j);
		k=j;
	}
}

struct NODE * delMin(struct NODE *nodes[], int heapSize){

//	printf("delMax.1\n");
	struct NODE *max = nodes[1];
//	printf("delMax.2\n");
	exch(nodes, 1, heapSize-1);

//	printf("delMax.3\n");
	sink(nodes, heapSize-1, 1);
//	printf("delMax.4\n");
	return max;
}

void exch(struct NODE *nodes[], int a, int b){
	struct NODE *tmp = nodes[a];
	nodes[a] = nodes[b];
	nodes[b] = tmp;
}

int compare(struct NODE *a, struct NODE *b){
	if(a->weight < b->weight){
		return 1;
	}else if(a->weight > b->weight){
		return -1;
	}else{
		return 0;
	}
}

void printHeap(struct NODE *heap[], int heapSize){

	while(heapSize > 1){
		struct NODE *max = delMin(heap, heapSize);
		heapSize--;
		printf("node.index=%d, node.weight=%d, heapSize=%d\n", max->letterIndex, max->weight, heapSize);
	}
}

