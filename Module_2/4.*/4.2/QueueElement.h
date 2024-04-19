#ifndef QUEUEELEMENT_H
#define QUEUEELEMENT_H

typedef struct QueueElement{
    unsigned char priority; // Приоритет от 0 до 255
    int data;
} QueueElement;


#endif