#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Очередь чз вектор
typedef enum {
    ok = 0,
    empty = 1,
}status_;




Info* infoGen(int k){
    /*Инициаллизация структуры Info
    *Входные данные: данные очереди(в данном случае одно число int)
    *Выходные данные: Объект Info*
    */
    Info* buf = (Info*)calloc(1, sizeof(Info));
    buf->k = k;
    return buf;
}

void queuePrint(Queue *d) {
    /*Вывод очереди
    *Входные данные: Очередь
    *Выходные данные: NULL
    */
    QueueUnit *iter = d->head;
    while (iter) {
        if (iter->info->k) printf("%2d\n", iter->info->k);
        iter = iter->next;
    }
    printf("\n");
}


Queue* queueInit(){
    /*Инициаллизация очереди (выделение памяти)
    *Входные данные: Null
    *Выходные данные: Объект Queue*
     */
    Queue* buf = (Queue*)calloc(1, sizeof(Queue));
    return buf;
}

int queueInsert(Queue *d, int k){
    /*Вставка элемента
    *Входные данные: Очередь, информация
    *Выходные данные: Статус ошибки
    */
    Info *inf = infoGen(k);
    QueueUnit *unit = (QueueUnit*)calloc(1, sizeof(QueueUnit));
    unit->info = inf;
    if (!(d->head)){
        d->head = unit;
        d->tail = unit;
    }
    else{
        d->tail->next = unit;
        d->tail = unit;
    }
    return ok;
}


int queueDelete(Queue *d){
    /*Удаление элемента
   *Входные данные: Очередь
   *Выходные данные: Статус ошибки
   */
    if (!(d->tail)) return empty;
    QueueUnit *buf = d->head;
    if (d->tail == d->head){
        d->tail = NULL;
        d->head = NULL;
    }
    else {
        d->head = d->head->next;
    }
    if (buf->info) free(buf->info);
    free(buf);
    return ok;
}

void queueFree(Queue *d){
    /*Очистка памяти Очереди
    *Входные данные: Очередь
    *Выходные данные: NULL
    */
    QueueUnit *iter = d->head;
    while (iter){
        QueueUnit *buf = iter->next;
        if (iter->info) free(iter->info);
        free(iter);
        iter = buf;
    }
}


