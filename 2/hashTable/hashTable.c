#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum{
    ok = 0,
    full = 1,
    empty = 3,
    notfound = -1,
    elAlreadyExist = 2,
}status_;


Info* infoGen(int d){
    /* Инициаллизация данных таблицы
    * Входные данные: сами данные (в данном случае одно число)
    * Выходные данные: Объект Info*
    */
    Info* buf = (Info*)calloc(1, sizeof(Info));
    buf->k = d;
    return buf;
}


void tablePrint(hashT* tab){
    printf("%5s %5s %5s\n","busy", "key", "info");
    for (int i = 0; i < tab->n; i++){
        if (tab->els[i].busy == 1){
            if (tab->els[i].inf) printf("%5d %5d %5d\n", tab->els[i].busy, tab->els[i].key, tab->els[i].inf->k);
        }
        else {
            printf("%5d\n", tab->els[i].busy);
        }
    }
    printf("\n");
}

hashT* tableInit(int n){
    /* Инициаллизация таблицы
     * Входные данные: размер таблицы
     * Выходные данные: Объект таблицы
     */

    hashT* table = (hashT*)calloc(1, sizeof(hashT));
    table->n = n;
    table->els = (hashUnit*)calloc(n, sizeof(hashUnit));
    return table;
}

int hashFunction(int x, int n){
    return x % n;
}

int tableFind(hashT* tab, int key){
    /* Поиск по ключу
    * Входные данные: таблица, ключ
    * Выходные данные: позиция в массиве или notfound
    */
    int i = 0;
    int hRes = hashFunction(key, tab->n);
    int pos = hRes;
    while (i <= tab->lvl){
        if (tab->els[pos].busy == 0) return notfound;
        if ((tab->els[pos].key == key) && (tab->els[pos].busy == 1)) return pos;
        i++;
        pos = (hRes + i) % tab->n;
    }
    return notfound;
}

int tableAdd(hashT* tab, int key, int d){
    /* Добавление элемента
    * Входные данные: таблица, ключ, данные
    * Выходные данные: статус
    */
    if (tab->lvl == tab->n) return full;
    int pos = tableFind(tab, key);
    if (pos != notfound) return elAlreadyExist;
    int i = 0;
    int hRes = hashFunction(key, tab->n);
    pos = hRes;
    while(tab->els[pos].busy != 0){
        i++;
        pos = (hRes + i) % tab->n;
    }
    tab->els[pos].busy = 1;
    tab->els[pos].key = key;
    Info* inf = infoGen(d);
    tab->els[pos].inf = inf;
    tab->lvl = tab->lvl + 1;
    return ok;
}


int tableDelete(hashT* tab, int key){
    /* Удаление элемента
    * Входные данные: таблица, ключ
    * Выходные данные: статус
    */
    if (tab->lvl == 0) return empty;
    int pos = tableFind(tab, key);
    if (pos == notfound) return notfound;
    tab->els[pos].busy = -1;
    if (tab->els[pos].inf) free(tab->els[pos].inf);
    tab->els[pos].inf = NULL;
    tab->lvl = tab->lvl - 1;
    return ok;
}

void tableFree(hashT* tab){
    for (int i = 0; i < tab->n; i++){
        if (tab->els[i].busy == 1){
            if (tab->els[i].inf) free(tab->els[i].inf);
        }
    }
    free(tab->els);
    free(tab);
}