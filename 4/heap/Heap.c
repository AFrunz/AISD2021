#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
#include <string.h>
#include <math.h>
#include <time.h>
#include "Heap.h"



void array_print(Tree* t){
    Unit** buf = t->unit;
    for (int i = 0; i < t->lvl; i++, buf++){
        if (*buf) {
            printf("%u ", (*buf)->key);
            Info* buf1 = (*buf)->inf;
            while (buf1){
                printf("%d %s ", buf1->relise, buf1->s);
                buf1 = buf1->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

Tree* init_tree(int n){
    Tree* buf = (Tree*)calloc(1, sizeof(Tree));
    buf->unit = (Unit**)calloc(n, sizeof(Unit*));
    buf->n = n;
    return buf;
}


int find_unit_rec(Tree* t, int pos, unsigned int key){
    if (pos >= t->lvl) return -1;

    if (t->unit[pos]->key == key) return pos;
    if (t->unit[pos]->key < key) return -1;
    int status1 = find_unit_rec(t, pos * 2 + 1, key);
    int status2 = find_unit_rec(t, pos * 2 + 2, key);
    if (status1 != -1) return status1;
    if (status2 != -1) return status2;
    return -1;
}


int find_unit(Tree* t, unsigned int key){
    if (!t) return -1;
    return find_unit_rec(t, 0, key);
}


int add_unit(Tree* t, unsigned int key, char* s){
    int status = find_unit(t, key);
    if (t->lvl >= t->n) return -1;
//    Если ключ уже есть
    if (status != -1){
        Unit **buf = t->unit + status;
        Info *inf = (Info*)calloc(1, sizeof(Info));
        inf->s = s;
        inf->next = (*buf)->inf;
        t->unit[status]->inf = inf;
        inf->relise = inf->next->relise + 1;
        return 0;
    }
//  Если ключ не существует
    Info *inf = (Info*)calloc(1, sizeof(Info));
    inf->s = s;
    Unit* buf = (Unit*)calloc(1, sizeof(Unit));
    buf->key = key;
    buf->inf = inf;
    t->unit[t->lvl] = buf;
    int lvl_in = t->lvl;
    while (buf->key > t->unit[(lvl_in - 1) / 2]->key){
        t->unit[lvl_in] = t->unit[(lvl_in - 1) / 2];
        t->unit[(lvl_in - 1) / 2] = buf;
        lvl_in = (lvl_in - 1) / 2;
    }
    t->lvl = t->lvl + 1;
    return 0;
}

void sift_down(Tree* t, int pos){
    if (pos >= t->lvl) return;
    if ((pos != 0) && (t->unit[(pos - 1) / 2]->key < t->unit[pos]->key)){
        Unit * buf = t->unit[(pos - 1) / 2];
        t->unit[(pos - 1) / 2] = t->unit[pos];
        t->unit[pos] = buf;
    }
    sift_down(t, pos * 2 + 1);
    sift_down(t, pos * 2 + 2);
}


int del_unit(Tree* t, unsigned int key, int version){
    int status = find_unit(t, key);
    if (status == -1) return -1;
    if (version != 0) {
        Info *buf = t->unit[status]->inf;
        Info *par = NULL;
        while (buf){
            if (buf->relise == version){
                if (par) {
                    par->next = buf->next;
                }
                else{
                    t->unit[status]->inf = buf->next;
                }
                free(buf);
                return 0;
            }
            par = buf;
            buf = buf->next;
            }
        return -2;
    }

    t->unit[status] = t->unit[t->lvl - 1];
    t->lvl = t->lvl - 1;
    array_print(t);
    sift_down(t, status);
    return 0;
}

void tree_print(Tree* t){
    FILE *f = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\bufs1234567.txt", "w");

    fprintf(f, "digraph grapht {\n");
    if (t->lvl == 1) fprintf(f, "%u;\n", t->unit[0]->key);
    for (int i = 1; i < t->lvl; i++){
        fprintf(f, "%u->%u\n", t->unit[(i - 1) / 2]->key, t->unit[i]->key);
    }
    fprintf(f, "}");
    fclose(f);
    system("C:\\Users\\frunz\\Graphviz\\bin\\dot.exe -Tpng -o C:/Users/frunz/Desktop/c_or_c++/C/logs/test.png C:/Users/frunz/Desktop/c_or_c++/C/logs/bufs1234567.txt");
    system("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\test.png");

}

void conditional_print(Tree* t, unsigned int key1, unsigned int key2){
    Unit **step = t->unit;
    Queue *q = Queue_init();
    if (key1 < key2) {
        for (int i = 0; i < t->lvl; i++, step++) {
            QueueUp_write(q, *step);
        }
    }
    else {
        for (int i = 0; i < t->lvl; i++, step++) {
            QueueDown_write(q, *step);
        }
    }
    if (key1 < key2){
      Unit* buf = NULL;
      while (q->head){
          Queue_read(q, &buf);
          if (buf->key > key2) break;
          if (buf->key >= key1) printf("%u ", buf->key);
      }
      printf("\n");
    }
    else {
        Unit* buf = NULL;
        while (q->head){
            Queue_read(q, &buf);
            if (buf->key < key2) break;
            if (buf->key <= key1) printf("%u ", buf->key);
        }
        printf("\n");
    }
}

Unit* find_max(Tree* t, unsigned int key){
    Unit **step = t->unit;
    Queue *q = Queue_init();
    for (int i = 0; i < t->lvl; i++, step++){
        QueueUp_write(q, *step);
    }
    Unit *buf1 = NULL;
    Unit *buf2 = NULL;
    while (q->head){
        Queue_read(q, &buf1);
        if (buf1->key > key) return buf2;
        buf2 = buf1;
    }
    return buf2;
}