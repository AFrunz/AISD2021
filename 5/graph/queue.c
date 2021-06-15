#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct Queue1{
    Graph* k1;
    struct Queue1* next;
}Queue1;


typedef struct Queue{
    Queue1 *head;
    int n;
}Queue;


Queue* Queue_init(){
    Queue *a;
    a = (Queue*)calloc(1, sizeof(Queue));
    a->head = NULL;
    a->n = 0;
    return a;
}

//int Queue_find(Queue* a, Graph* b){
//    Queue1* buf = a->head;
//    while (buf){
//        if (buf->k1 == b){
//            return 1;
//        }
//        buf = buf->next;
//    }
//    return 0;
//}

Queue1 *QueueUp_find(Queue* a, Graph* b, float* key, Queue1** par){
    Queue1* buf = a->head;
    while (buf){
        if (buf->k1 == b){
            return buf;
        }
        if (par) {
            *par = buf;
        }
        buf = buf->next;
    }
    return NULL;
}

void Queue_print(Queue* a){
    Queue1* buf = a->head;
    while (buf){
        printf("%s ",buf->k1->key);
        buf = buf->next;
    }
    printf("\n");
}



void QueueUp_write(Queue *a, Graph *k1, float *key) {
    Queue1 *c = (Queue1*)calloc(1, sizeof(Queue1));
    Queue1 *buf = a->head;
    Queue1 *par = NULL;
    c->k1 = k1;
    if (!buf){
        a->head = c;
        a->n = a->n + 1;
        return;
    }
    while (buf){
        if (key[buf->k1->k] > key[k1->k]){
            if (par){
                par->next = c;
                c->next = buf;
            }
            else{
                a->head = c;
                c->next = buf;
            }
            a->n = a->n + 1;
            return;
        }
        par = buf;
        buf = buf->next;
    }
    par->next = c;
    a->n = a->n + 1;
}

void Change_list(Queue* a, float* key,  Graph* k1 , float new){
    Queue1* par = NULL;
    Queue1* el = QueueUp_find(a, k1, key, &par);
    Queue1* step = a->head;
    Queue1* par1 = NULL;
    while (step){
        if (key[step->k1->k] > key[el->k1->k]){
            if (par) {
                par->next = el->next;
            }
            else {
                a->head = el->next;
            }
            if (!par1 || par1 == el){
                Queue1 * buf = a->head;
                a->head = el;
                el->next = buf;
            }
            else {
                Queue1 * buf = par1->next;
                par1->next = el;
                el->next = buf;
            }
            return;
        }
        par1 = step;
        step = step->next;
    }
    if (par1) {
        par1->next = el;
        if (par) {
            par->next = el->next;
        }
        else {
            a->head = el->next;
        }
        el->next = NULL;
    }
    else {
        a->head = el;
        par->next = el->next;
        el->next = NULL;
    }
}



int Queue_read(Queue* a, Graph **b){
    Queue1 *x = NULL;
    if (a->head != NULL){
        x = a->head;
        a->n = a->n - 1;
        a->head = a->head->next;
        *b = x->k1;
        return 0;
    }
    else{
        return -1;
    }
}

