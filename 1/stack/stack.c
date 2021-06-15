#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Стэк чз вектор
typedef enum {
    ok = 0,
    empty = 1,
}status_;




Info* infoGen(int k){
    /*Инициаллизация структуры Info
    *Входные данные: данные дека(в данном случае одно число int)
    *Выходные данные: Объект Info*
    */
    Info* buf = (Info*)calloc(1, sizeof(Info));
    buf->k = k;
    return buf;
}

void stackPrint(Stack *d) {
    /*Вывод очереди
    *Входные данные: Стэк
    *Выходные данные: NULL
    */
    StackUnit *iter = d->head;
    while (iter) {
        if (iter->info->k) printf("%2d\n", iter->info->k);
        iter = iter->next;
    }
    printf("\n");
}


Stack* stackInit(){
    /*Инициаллизация стэка (выделение памяти)
    *Входные данные: Null
    *Выходные данные: Объект Stack*
     */
    Stack* buf = (Stack*)calloc(1, sizeof(Stack));
    return buf;
}

int stackInsert(Stack *d, int k){
    /*Вставка элемента
    *Входные данные: Стэк, информация
    *Выходные данные: Статус ошибки
    */
    Info *inf = infoGen(k);
    StackUnit *unit = (StackUnit*)calloc(1, sizeof(StackUnit));
    unit->info = inf;
    if (!(d->head)){
        d->head = unit;
    }
    else{
        unit->next = d->head;
        d->head = unit;
    }
    return ok;
}


int stackDelete(Stack *d){
    /*Удаление элемента
   *Входные данные: Стэк
   *Выходные данные: Статус ошибки
   */
    if (!(d->head)) return empty;
    StackUnit *buf = d->head;
    d->head = d->head->next;
    if (buf->info) free(buf->info);
    free(buf);
    return ok;
}

void stackFree(Stack *d){
    /*Очистка памяти стэка
    *Входные данные: Стэк
    *Выходные данные: NULL
    */
    StackUnit *iter = d->head;
    while (iter){
        StackUnit *buf = iter->next;
        if (iter->info) free(iter->info);
        free(iter);
        iter = buf;
    }
}


