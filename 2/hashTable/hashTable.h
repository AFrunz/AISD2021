#ifndef BD_HASHTABLE_H
#define BD_HASHTABLE_H

typedef struct Info{
    int k;
}Info;

typedef struct hashUnit{
    Info* inf;
    int busy;
    int key;
}hashUnit;

typedef struct hashT{
    int n;
    int lvl;
    hashUnit *els;
}hashT;



void tablePrint(hashT* tab);

hashT* tableInit(int n);

int tableFind(hashT* tab, int key);

int tableAdd(hashT* tab, int key, int d);

int tableDelete(hashT* tab, int key);

void tableFree(hashT* tab);


#endif
