// queue.c
#include <stdio.h>
#include "queue.h"
#include <stdlib.h>
#include "../process.h"

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

int isEmpty(Queue *q)
{
    return q->front > q->rear;
}

int isFull(Queue *q)
{
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, Process p)
{
    if (isFull(q))
    {
        printf("Queue Overflow!\n");
        return;
    }
    q->rear++;
    q->data[q->rear] = p;
}

Process dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue Underflow!\n");
        Process empty = {-1}; // error value
        return empty;
    }
    return q->data[q->front++];
}
