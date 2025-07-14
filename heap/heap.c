// heap.c
#include "heap.h"

void initHeap(MinHeap *h, Comparator cmp)
{
    h->size = 0;
    h->cmp = cmp;
}

void swap(Process *a, Process *b)
{
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void insertHeap(MinHeap *h, Process p)
{
    int i = h->size++;
    h->data[i] = p;

    while (i != 0 && h->cmp(h->data[i], h->data[(i - 1) / 2]))
    {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Process extractMin(MinHeap *h)
{
    Process min = h->data[0];
    h->data[0] = h->data[--h->size];

    int i = 0;
    while (1)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < h->size && h->cmp(h->data[left], h->data[smallest]))
            smallest = left;
        if (right < h->size && h->cmp(h->data[right], h->data[smallest]))
            smallest = right;

        if (smallest == i)
            break;

        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }

    return min;
}

int isHeapEmpty(MinHeap *h)
{
    return h->size == 0;
}
