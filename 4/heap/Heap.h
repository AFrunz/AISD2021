#ifndef C_HEAP_H
#define C_HEAP_H

typedef struct Info{
    int relise;
    struct Info* next;
    char *s;
}Info;

typedef struct Unit{
    unsigned int key;
    Info* inf;
}Unit;

typedef struct Tree{
    Unit** unit;
    int lvl;
    int n;
}Tree;

Tree* init_tree(int n);

void array_print(Tree* t);

int find_unit(Tree* t, unsigned int key);

int add_unit(Tree* t, unsigned int key, char* s);

int del_unit(Tree* t, unsigned int key, int version);

void tree_print(Tree* t);

void conditional_print(Tree* t, unsigned int key1, unsigned int key2);

Unit* find_max(Tree* t, unsigned int key);


#endif //C_HEAP_H
