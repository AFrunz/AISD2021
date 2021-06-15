#ifndef BD_VIEWTABLE_H
#define BD_VIEWTABLE_H

typedef struct Info{
    int k;
}Info;

typedef struct viewUnit{
    Info* inf;
    int key;
}viewUnit;

typedef struct viewT{
    int n;
    int lvl;
    viewUnit *els;
}viewT;

void tablePrint(viewT* tab);

viewT* tableInit(int n);

int tableFind(viewT* tab, int key);

int tableAdd(viewT* tab, int key, int d);

int tableDelete(viewT* tab, int key);

void tableFree(viewT* tab);


#endif
