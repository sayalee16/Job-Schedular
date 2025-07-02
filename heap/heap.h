// heap.h
#ifndef HEAP_H
#define HEAP_H

#include "../process.h"

#define MAX_HEAP 100

typedef int (*Comparator)(Process a, Process b);

typedef struct
{
    Process data[MAX_HEAP];
    int size;
    Comparator cmp;
} MinHeap;



void initHeap(MinHeap *h,Comparator cmp);
void insertHeap(MinHeap *h, Process p);
Process extractMin(MinHeap *h);
int isHeapEmpty(MinHeap *h);

#endif
