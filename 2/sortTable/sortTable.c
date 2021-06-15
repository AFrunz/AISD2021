#include "sortTable.h"
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

void tablePrint(sortT* tab){
    /* Печать таблицы
    * Входные данные: таблица
    * Выходные данные: NULL
    */
    sortUnit *t = tab->els;
    printf("%4s %4s", "key", "info\n");
    for (int i = 0; i < tab->lvl; i++, t++){
        if (t->inf) printf("%4d %4d\n", t->key, t->inf->k);
    }
    printf("\n");
}

sortT* tableInit(int n){
    /* Инициаллизация таблицы
    * Входные данные: размер таблицы
    * Выходные данные: Объект sortT*
    */
    sortT* tab = (sortT*)calloc(1, sizeof(sortT));
    tab->n = n;
    tab->els = (sortUnit*)calloc(n, sizeof(sortUnit));
    return tab;
}

int tableFind(sortT* tab, int key){
    /* Поиск по таблице
    * Входные данные: Таблица и ключ
    * Выходные данные: Индекс эл-та или notfound
    */
    int l = 0;
    int u = tab->lvl - 1;
    if (u == -1) return notfound;
    while (u != l){
        int sr = (u + l) / 2;
        if (tab->els[sr].key == key) return sr;
        if ((sr == l) || (sr == u)) break;
        if (tab->els[sr].key > key) u = sr;
        if (tab->els[sr].key < key) l = sr;
    }
    if (tab->els[u].key == key) return u;
    return notfound;
}

int tableAdd(sortT* tab, int key, int d){
    /* Добавление эл-та в таблицу
    * Входные данные: Таблица, ключ и информация
    * Выходные данные: статус
    */
    if (tab->lvl == tab->n) return full;
    int pos = tableFind(tab, key);
    if (pos != notfound) return elAlreadyExist;
    for (int i = tab->lvl; i > 0; i--){
        if (tab->els[i - 1].key < key){
            tab->els[i].key = key;
            Info* inf = infoGen(d);
            tab->els[i].inf = inf;
            tab->lvl = tab->lvl + 1;
            return ok;
        }
        tab->els[i].key = tab->els[i - 1].key;
        tab->els[i].inf = tab->els[i - 1].inf;
    }
    tab->els[0].key = key;
    Info* inf = infoGen(d);
    tab->els[0].inf = inf;
    tab->lvl = tab->lvl + 1;
    return ok;
}

int tableDelete(sortT* tab, int key){
    /* Удаление эл-та из таблицы
    * Входные данные: Таблица и ключ
    * Выходные данные: статус
    */
    if (tab->lvl == 0) return empty;
    int pos = tableFind(tab, key);
    if (pos == notfound) return notfound;
    if (tab->els[pos].inf) free(tab->els[pos].inf);
    while(pos < tab->lvl - 1){
        tab->els[pos].key = tab->els[pos + 1].key;
        tab->els[pos].inf = tab->els[pos + 1].inf;
        pos++;
    }
    tab->lvl = tab->lvl - 1;
    return ok;
}

void tableFree(sortT* tab){
    /* Очистка памяти таблицы
    * Входные данные: Таблица
    * Выходные данные: NULL
    */
    sortUnit *t = tab->els;
    for (int i = 0; i < tab->lvl; i++, t++){
        if (t->inf) free(t->inf);
    }
    free(tab->els);
    free(tab);
}