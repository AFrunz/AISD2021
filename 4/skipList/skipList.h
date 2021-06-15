#ifndef BD_SKIPLIST_H
#define BD_SKIPLIST_H
#define Max_level 2
#include "limits.h"

typedef struct Info{
    int d;
}Info;

typedef struct Item{
    int key;
    Info* inf;
    int lvl;
    struct Item* forwards[Max_level];
}Item;


typedef struct skList{
    int lvl;
    struct Item* header;
}skList;


skList *listInit();

Item* listFind(skList* list, int key);

int listAdd(skList* list, int key, int d);

void listPrint(skList* list);

int listDelete(skList* list, int key);


#endif
