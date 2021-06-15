#include "skipList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define p 0.6

typedef enum{
    ok = 0,
    notfound = -1,
    elAlreadyExist = -2,
}status_;

struct Item EList = {INT_MAX};

Info* infoGen(int d){
    /* Инициаллизация данных таблицы
    * Входные данные: сами данные (в данном случае одно число)
    * Выходные данные: Объект Info*
    */
    Info* buf = (Info*)calloc(1, sizeof(Info));
    buf->d = d;
    return buf;
}

double random(){
    double t =  ((double)rand() - 1)/RAND_MAX;
    return t;
}

int level_gen(){
    /* Генерация уровня
     * Входные данные: коэф p
     * Выходные данные: количество уровней
     */
    int level = 1;
    while ((random() < p) && (level < Max_level)){
        level++;
    }
    return level;
}

skList *listInit(){
    srand(time(NULL));
    skList* list = (skList*)calloc(1, sizeof(skList));
    list->header = (Item*)calloc(1, sizeof(Item));
    for (int i = 0; i < Max_level; i++){
        list->header->forwards[i] = &EList;
    }
    return list;
}


Item* listFind(skList* list, int key){
    /* Поиск по списку
     * Входные данные: список, ключ
     * Выходные данные: указатель на эл-т или NULL
     */
    Item* x = list->header;
    for (int i = list->lvl - 1; i >= 0; i--){
        while (x->forwards[i]->key < key){
            x = x->forwards[i];
        }
        if (x->forwards[i]->key == key) return x->forwards[i];
    }
    return NULL;
}

int listAdd(skList* list, int key, int d){
    /* Добавление нового элемента
     * Входные данные: список, ключ, информация
     * Выходные данные: статус
     */
    Item* x = list->header;
    Item* update[Max_level];

    for (int i = list->lvl - 1; i >= 0; i--){
        while (x->forwards[i]->key < key){
            x = x->forwards[i];
        }
        update[i] = x;
    }
    x = x->forwards[0];
    if (x) {
        if (x->key == key) return elAlreadyExist;
    }
    int level = level_gen();
    if (list->lvl < level){
        for (int j = list->lvl; j < level; j++){
            update[j] = list->header;
        }
        list->lvl = level;
    }
    Info* inf = infoGen(d);
    Item* el = (Item*)calloc(1, sizeof(Item));
    el->key = key;
    el->lvl = level;
    el->inf = inf;
    for (int i = 0; i < level; i++){
        el->forwards[i] = update[i]->forwards[i];
        update[i]->forwards[i] = el;
    }
    return ok;
}

int listDelete(skList* list, int key){
    Item *update[Max_level];
    Item* x = list->header;
    for (int i = list->lvl - 1; i >= 0; i--){
        while(x->forwards[i]->key < key){
            x = x->forwards[i];
        }
        update[i] = x;
    }
    x = x->forwards[0];
    if (x->key == key){
        int i = 0;
        while ((i < list->lvl) && (update[i]->forwards[i] == x)){
            update[i]->forwards[i] = x->forwards[i];
            i++;
        }
        if (x->inf) free(x->inf);
        free(x);
        while ((list->lvl > 1) && (list->header->forwards[list->lvl] == &EList)) {
            list->lvl = list->lvl - 1;
        }
        return ok;
    }
    return notfound;
}



void listPrint(skList* list){
    Item *x = list->header;
    for (int i = 0; i < list->lvl; i++){
        Item* buf = x->forwards[i];
        while (buf != &EList){
            printf("%4d ", buf->key);
            buf = buf->forwards[i];
        }
        printf("\n");
    }
}
