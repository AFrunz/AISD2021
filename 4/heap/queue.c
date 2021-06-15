#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

typedef struct Queue1{
    Unit* k1;
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


int QueueUp_find(Queue* a, Unit* b){
    Queue1* buf = a->head;
    while (buf){
        if (buf->k1 == b){
            return 1;
        }
        if (buf->k1->key > b->key) return 0;
        buf = buf->next;
    }
    return 0;
}

int QueueDown_find(Queue* a, Unit* b){
    Queue1* buf = a->head;
    while (buf){
        if (buf->k1 == b){
            return 1;
        }
        if (buf->k1->key < b->key) return 0;
        buf = buf->next;
    }
    return 0;
}


void Queue_print(Queue* a){
    Queue1* buf = a->head;
    while (buf){
        printf("%u ",buf->k1->key);
        buf = buf->next;
    }
}


void QueueUp_write(Queue* a, Unit* k1){
    Queue1 *c = (Queue1*)calloc(1, sizeof(Queue1));
    Queue1 *buf = a->head;
    Queue1 *par = NULL;
    c->k1 = k1;
    if (!buf){
        a->head = c;
        return;
    }
    while (buf){
        if (buf->k1->key > k1->key){
            if (par){
                par->next = c;
                c->next = buf;
            }
            else{
                a->head = c;
                c->next = buf;
            }
            return;
        }
        par = buf;
        buf = buf->next;
    }
    par->next = c;
}

void QueueDown_write(Queue* a, Unit* k1){
    Queue1 *c = (Queue1*)calloc(1, sizeof(Queue1));
    Queue1 *buf = a->head;
    Queue1 *par = NULL;
    c->k1 = k1;
    if (!buf){
        a->head = c;
        return;
    }
    while (buf){
        if (buf->k1->key < k1->key){
            if (par){
                par->next = c;
                c->next = buf;
            }
            else{
                a->head = c;
                c->next = buf;
            }
            return;
        }
        par = buf;
        buf = buf->next;
    }
    par->next = c;

}

int Queue_read(Queue* a, Unit **b){
    if (!a->head) return -1;
    Queue1 *buf = a->head;
    a->head = buf->next;
    *b = buf->k1;
    return 0;
}




//int Queue_read(Queue* a, Unit **b){
//    Queue1 *x = NULL;
//    if (a->head != NULL){
//        x = a->head;
//        a->n = a->n - 1;
//        a->head = a->head->next;
//        *b = x->k1;
//        return 0;
//    }
//    else{
//        return -1;
//    }
//}

//
//int Queue_read_min(Queue* a, Unit **b){
//    if (!a->head) return -1;
//    Queue1 *step = a->head;
//    Queue1 *par = NULL;
//    unsigned int max = step->k1->key;
//    Queue1 *buf = step;
//    Queue1 *par_buf = NULL;
//    while (step){
//        if (step->k1->key < max){
//            max = step->k1->key;
//            buf = step;
//            par_buf = par;
//        }
//
//        par = step;
//        step = step->next;
//    }
//    if (par_buf){
//        par_buf->next = buf->next;
//        *b = buf->k1;
//        free(buf);
//        a->n = a->n - 1;
//        return 0;
//    }
//    else {
//        a->head = buf->next;
//        *b = buf->k1;
//        free(buf);
//        a->n = a->n - 1;
//        return 0;
//    }
//}
//
//
//int Queue_read_max(Queue* a, Unit **b){
//    if (!a->head) return -1;
//    Queue1 *step = a->head;
//    Queue1 *par = NULL;
//    unsigned int max = step->k1->key;
//    Queue1 *buf = step;
//    Queue1 *par_buf = NULL;
//    while (step){
//        if (step->k1->key > max){
//            max = step->k1->key;
//            buf = step;
//            par_buf = par;
//        }
//
//        par = step;
//        step = step->next;
//    }
//    if (par_buf){
//        par_buf->next = buf->next;
//        *b = buf->k1;
//        free(buf);
//        a->n = a->n - 1;
//        return 0;
//    }
//    else {
//        a->head = buf->next;
//        *b = buf->k1;
//        free(buf);
//        a->n = a->n - 1;
//        return 0;
//    }
//}