#ifndef BD_SORTTABLE_H
#define BD_SORTTABLE_H

typedef struct Info{
    int k;
}Info;

typedef struct sortUnit{
    Info* inf;
    int key;
}sortUnit;

typedef struct sortT{
    int n;
    int lvl;
    sortUnit *els;
}sortT;


void tablePrint(sortT* tab);

sortT* tableInit(int n);

int tableFind(sortT* tab, int key);

int tableAdd(sortT* tab, int key, int d);

int tableDelete(sortT* tab, int key);

void tableFree(sortT* tab);



#endif //BD_SORTTABLE_H
