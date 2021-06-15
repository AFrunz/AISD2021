#ifndef BD_QUEUE_H
#define BD_QUEUE_H


typedef struct Info{
    int k;
}Info;

typedef struct QueueUnit{
    struct QueueUnit *next;
    Info *info;
}QueueUnit;

typedef struct Queue{
    QueueUnit *head, *tail;
}Queue;

void queuePrint(Queue *d);

Queue* queueInit();

int queueInsert(Queue *d, int k);

int queueDelete(Queue *d);

void queueFree(Queue *d);




#endif //BD_QUEUE_H
