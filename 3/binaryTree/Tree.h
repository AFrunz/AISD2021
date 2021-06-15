#ifndef C_TREE_H
#define C_TREE_H

typedef struct Info{
    int relise;
    struct Info* next;
    char *s;
}Info;


typedef struct unit {
    unsigned int key;
    struct unit *left;
    struct unit *right;
    struct unit *parent;
    struct unit *next;
    struct unit *previous;
    Info* info;
}unit;

void print_next(unit *root);

void print_previous(unit *root);

void print_unit(unit *el);

unit *target(unit *root, unsigned int key);

unit* add_unit(unsigned int key, char *inf, unit *root);

unit* find_union(unsigned int key, unit *root);

Info* find_inf(unit* r, int k);

void tree_printf(unit* root, int a, int b);

unit* find_next(unit *x, unit *root);

unit* del_unit(unsigned int key, unit *root, int k, int* status);

unit* find_maxi(unsigned int key, unit *root);

void tree_print_v3(unit* root, int lvl);

void Time_tree();

void tree_free(unit* root);

void gr_print(unit* root);

#endif //C_TREE_H
