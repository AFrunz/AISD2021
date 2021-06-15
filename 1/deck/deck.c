#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

// Дек чз вектор
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

void deckPrint(Deck *d) {
    /*Вывод дека
    *Входные данные: Дэк
    *Выходные данные: NULL
    */
    DeckUnit *iter = d->head;
    while (iter) {
        if (iter->info->k) printf("%2d\n", iter->info->k);
        iter = iter->next;
    }
    printf("\n");
}


Deck* deckInit(){
    /*Инициаллизация дека (выделение памяти)
    *Входные данные: Null
    *Выходные данные: Объект Deck*
     */
    Deck* buf = (Deck*)calloc(1, sizeof(Deck));
    return buf;
}

int deckInsertHead(Deck *d, int k){
    /*Вставка элемента в начало
    *Входные данные: Дэк, информация
    *Выходные данные: Статус ошибки
    */
    Info *inf = infoGen(k);
    DeckUnit *unit = (DeckUnit*)calloc(1, sizeof(DeckUnit));
    unit->info = inf;
    if (!(d->head)){
        d->head = unit;
        d->tail = unit;
    }
    else{
        unit->next = d->head;
        d->head->parent = unit;
        d->head = unit;
    }
    return ok;
}

int deckInsertTail(Deck *d, int k){
    /*Вставка элемента в конец
    *Входные данные: Дэк, информация
    *Выходные данные: Статус ошибки
    */
    Info *inf = infoGen(k);
    DeckUnit *unit = (DeckUnit*)calloc(1, sizeof(DeckUnit));
    unit->info = inf;
    if (!(d->head)){
        d->head = unit;
        d->tail = unit;
    }
    else{
        unit->parent = d->tail;
        d->tail->next = unit;
        d->tail = unit;
    }
    return ok;
}

int deckDeleteHead(Deck *d){
    /*Удаление первого элемента
    *Входные данные: Дэк
    *Выходные данные: Статус ошибки
    */
    if (!(d->head)) return empty;
    DeckUnit *buf = d->head;
    if (d->tail == d->head){
        d->tail = NULL;
        d->head = NULL;
    }
    else {
        d->head = d->head->next;
        d->head->parent = NULL;
    }
    if (buf->info) free(buf->info);
    free(buf);
    return ok;
}

int deckDeleteTail(Deck *d){
    /*Удаление последнего элемента
   *Входные данные: Дэк
   *Выходные данные: Статус ошибки
   */
    if (!(d->tail)) return empty;
    DeckUnit *buf = d->tail;
    if (d->tail == d->head){
        d->tail = NULL;
        d->head = NULL;
    }
    else {
        d->tail = d->tail->parent;
        d->tail->next = NULL;
    }
    if (buf->info) free(buf->info);
    free(buf);
    return ok;
}

void deckFree(Deck *d){
    /*Очистка памяти дека
    *Входные данные: Дэк
    *Выходные данные: NULL
    */
    DeckUnit *iter = d->head;
    while (iter){
        DeckUnit *buf = iter->next;
        if (iter->info) free(iter->info);
        free(iter);
        iter = buf;
    }
}


