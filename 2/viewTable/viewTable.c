#include "viewTable.h"
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


void tablePrint(viewT* tab){
    /* Печать таблицы
    * Входные данные: таблица
    * Выходные данные: NULL
    */
    viewUnit *t = tab->els;
    printf("%4s %4s", "key", "info\n");
    for (int i = 0; i < tab->lvl; i++, t++){
        if (t->inf) printf("%4d %4d\n", t->key, t->inf->k);
    }
    printf("\n");
}

viewT* tableInit(int n){
    /* Инициаллизация таблицы
    * Входные данные: размер таблицы
    * Выходные данные: Объект viewT*
    */
    viewT* tab = (viewT*)calloc(1, sizeof(viewT));
    tab->n = n;
    tab->els = (viewUnit*)calloc(n, sizeof(viewUnit));
    return tab;
}

int tableFind(viewT* tab, int key){
    /* Поиск по таблице
    * Входные данные: Таблица и ключ
    * Выходные данные: Индекс эл-та или notfound
    */
    viewUnit *iter = tab->els;
    for (int i = 0; i < tab->lvl; i++, iter++){
        if (iter->key == key) return i;
    }
    return notfound;
}

int tableAdd(viewT* tab, int key, int d){
    /* Добавление эл-та в таблицу
    * Входные данные: Таблица, ключ и информация
    * Выходные данные: статус
    */
    if (tab->lvl == tab->n) return full;
    int pos = tableFind(tab, key);
    if (pos != notfound) return elAlreadyExist;
    tab->els[tab->lvl].key = key;
    Info* inf = infoGen(d);
    tab->els[tab->lvl].inf = inf;
    tab->lvl = tab->lvl + 1;
    return ok;
}

int tableDelete(viewT* tab, int key){
    /* Удаление эл-та из таблицы
    * Входные данные: Таблица и ключ
    * Выходные данные: статус
    */
    if (tab->lvl == 0) return empty;
    int pos = tableFind(tab, key);
    if (pos == notfound) return notfound;
    if (pos != tab->lvl - 1){
//        Info* buf = tab->els[pos].inf;
        if (tab->els[pos].inf) free(tab->els[pos].inf);
        tab->els[pos] = tab->els[tab->lvl - 1];
//        if (buf) free(buf);
    }
    else {
        if (tab->els[tab->lvl - 1].inf) free(tab->els[tab->lvl - 1].inf);
    }
        tab->lvl = tab->lvl - 1;
        return ok;
}

void tableFree(viewT* tab){
    /* Очистка памяти таблицы
    * Входные данные: Таблица
    * Выходные данные: NULL
    */
    viewUnit *t = tab->els;
    for (int i = 0; i < tab->lvl; i++, t++){
        if (t->inf) free(t->inf);
    }
    free(tab->els);
    free(tab);
}