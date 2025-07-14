// queue.h
#ifndef QUEUE_H
#define QUEUE_H

#include "../process.h"

#define MAX 100

typedef struct
{
    Process data[MAX];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void cenqueue(Queue *q, Process p);
Process cdequeue(Queue *q);

#endif
