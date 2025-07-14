// queue.c
#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int isEmpty(Queue *q)
{
    return q->size == 0;
}

int isFull(Queue *q)
{
    return q->size == MAX;
}

void cenqueue(Queue *q, Process p)
{
    if (isFull(q))
    {
        printf("Queue Overflow!\n");
        return;
    }

    q->data[q->rear] = p;
    q->rear = (q->rear + 1) % MAX;
    q->size++;
}

Process cdequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Underflow!\n");
        Process empty = {.pid = -1};
        return empty;
    }

    Process p = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return p;
}
