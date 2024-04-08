#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>


PriorityQueue* initPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->size = 0;
    return pq;
}

void enqueue(PriorityQueue* pq, unsigned char priority, int data) {
    if (pq->size >= MAX_SIZE) {
        printf("Queue is full\n");
        return;
    }
    
    QueueElement newElement;
    newElement.priority = priority;
    newElement.data = data;

    int i = pq->size++;
    while (i > 0 && pq->heap[(i - 1) / 2].priority > priority) {
        pq->heap[i] = pq->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    pq->heap[i] = newElement;
}

void swap(QueueElement* a, QueueElement* b) {
    QueueElement temp = *a;
    *a = *b;
    *b = temp;
}

QueueElement dequeue(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Queue is empty\n");
    }

    QueueElement minElement = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];

    int i = 0;
    while (2 * i + 1 < pq->size) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        int minChild = leftChild;

        if (rightChild < pq->size && pq->heap[rightChild].priority < pq->heap[leftChild].priority) {
            minChild = rightChild;
        }

        if (pq->heap[i].priority <= pq->heap[minChild].priority) {
            break;
        }

        swap(&pq->heap[i], &pq->heap[minChild]);
        i = minChild;
    }

    return minElement;
}

QueueElement dequeueWithPriority(PriorityQueue* pq, int priority) {
    int i;
    for (i = 0; i < pq->size; ++i) {
        if (pq->heap[i].priority == priority) {
            break;
        }
    }

    if (i == pq->size) {
        printf("Element with priority %d not found\n", priority);
    }

    QueueElement element = pq->heap[i];

    for (int j = i; j < pq->size - 1; ++j) {
        pq->heap[j] = pq->heap[j + 1];
    }

    pq->size--;

    return element;
}

QueueElement dequeueWithPriorityNotLessThan(PriorityQueue* pq, int priority) {
    int i;
    for (i = 0; i < pq->size; ++i) {
        if (pq->heap[i].priority >= priority) {
            break;
        }
    }

    if (i == pq->size) {
        printf("Element with priority not less than %d not found\n", priority);
         QueueElement dummyElement;
        dummyElement.priority = -1; 
        return dummyElement;
    }

    QueueElement element = pq->heap[i];

    for (int j = i; j < pq->size - 1; ++j) {
        pq->heap[j] = pq->heap[j + 1];
    }

    pq->size--;

    return element;
}
