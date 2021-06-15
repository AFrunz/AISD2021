#ifndef C_AVLTREE_H
#define C_AVLTREE_H

typedef struct Info{
    int f1;
    int f2;
    char* s;
}Info;

typedef struct unit{
    int key;
    int balance;
    struct unit* parent;
    struct unit* right;
    struct unit* left;
    Info* info;
}unit;


void tree_print_v3(unit* root, int lvl);

Info* add_unit(unit**root, int key, Info *info);

unit* find_union(int key, unit *root);

unit* del_unit(int key, unit *root, int* status);

void print_max(unit* root, int key, int flag);

unit* max_dif(unit* root, int key);

void tree_free(unit* root);

void Time_tree();

void gr_print(unit* root);

#endif
