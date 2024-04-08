#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "QueueElement.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct {
    QueueElement heap[MAX_SIZE];
    int size;
} PriorityQueue;

PriorityQueue* initPriorityQueue();
void enqueue(PriorityQueue* pq, unsigned char priority, int data);
void swap(QueueElement* a, QueueElement* b);
QueueElement dequeue(PriorityQueue* pq) ;
QueueElement dequeueWithPriority(PriorityQueue* pq, int priority);
QueueElement dequeueWithPriorityNotLessThan(PriorityQueue* pq, int priority);

#endif