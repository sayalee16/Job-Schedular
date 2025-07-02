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
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, Process p);
Process dequeue(Queue *q);

#endif
