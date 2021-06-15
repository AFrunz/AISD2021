#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tree.h"



unit *target(unit *root, unsigned int key){
//    Поиск места для вставки
    unit* ptr = root;
    unit* par = NULL;
    while(ptr != NULL){
        par = ptr;
        if (key < ptr->key){
            ptr = ptr->left;
        }
        else if (key > ptr->key){
            ptr = ptr->right;
        }
        else return ptr;
    }
    return par;
}

unit* find_next2(unit* p, unit* x){
    while ((p->next) && (p->next->key < x->key)){
        p = p->next;
    }
    return p->next;
}

unit* find_previous(unit *p, unit *x){
    while ((p->previous) && (p->previous->key < x->key)){
        p = p->previous;
    }
    return p->previous;
}

unit* add_unit(unsigned int key, char *inf, unit *root){
///1) Включение нового элемента в таблицу без нарушения свойств упорядоченности;
    unit* ptr1 = NULL;
    unit* ptr2 = NULL;
    int version = 0;
//    Если дерева еще нет
    if (root == NULL){
        root = (unit*)calloc(1, sizeof(unit));
        (root)->key = key;
        (root)->info = (Info*)calloc(1, sizeof(Info));
        (root)->info->s = inf;
        return root;
    }
    else {
//        Поиск места
        ptr1 = target(root, key);
        ptr2 = ptr1;
//        Вставка вправо
        if (key > ptr1->key) {
            ptr1->right = (unit *) calloc(1, sizeof(unit));
            ptr1 = ptr1->right;
            ptr1->previous = ptr2;
            ptr1->next = find_next2(ptr2, ptr1);
            ptr2->next = ptr1;
            if (ptr1->next != NULL) ptr1->next->previous = ptr1;
//            Вставка влево
        } else if (key < ptr1->key) {
            ptr1->left = (unit *) calloc(1, sizeof(unit));
            ptr1 = ptr1->left;
            ptr1->next = ptr2;
            ptr1->previous = find_previous(ptr2, ptr1);
            ptr2->previous = ptr1;
            if (ptr1->previous != NULL) ptr1->previous->next = ptr1;
        }
//        Если элемент уже существует
        else {
            version = ptr1->info->relise + 1;
            Info* info = (Info*)calloc(1, sizeof(Info));
            info->relise = version;
            info->next = ptr1->info;
            info->s = inf;
            ptr1->info = info;
            return root;
        }
//        Добавление информации
        Info* info = (Info*)calloc(1, sizeof(Info));
        ptr1->key = key;
        info->s = inf;
        ptr1->info = info;
        ptr1->parent = ptr2;

    }
    return root;
}

unit* find_union(unsigned int key, unit *root){
    //3) Поиск информации по заданному ключу;
    unit *ptr = root;
    while (ptr != NULL){
        if (ptr->key > key){
            ptr = ptr->left;
        }
        else if (ptr->key < key){
            ptr = ptr->right;
        }
        else return ptr;
    }
    return NULL;
}

Info* find_inf(unit* r, int k){
    Info *inf = r->info;
    while (inf != NULL){
        if (inf->relise == k){
            return inf;
        }
        inf = inf->next;
    }
    return NULL;
}

void print_unit(unit *el) {
    printf("%10u ", el->key);
    Info *inf = el->info;
    while (inf != NULL) {
        printf("%10d %10s ",inf->relise, inf->s);
        inf = inf->next;
    }
    printf("\n");
}

void print_next(unit *root){
    if (!root) {
        printf("El not found\n");
        return;
    }
    while (root->left){
        root = root->left;
    }
    while (root){
        printf("%d ",root->key);
        root = root->next;
    }
    printf("\n");
}

void print_previous(unit *root){
    if (!root){
        printf("El not found\n");
        return;
    }
    while (root->right){
        root = root->right;
    }
    while (root){
        printf("%d ",root->key);
        root = root->previous;
    }
    printf("\n");
}

void tree_printf(unit* root, int a, int b){
//4) Вывод всего содержимого таблицы в заданном диапазоне значений ключей в указанном порядке их следования (a < key < b, (a, b) – прямой, (b, a) – обратный)
    if (a < b){
        if (root == NULL) return;
        tree_printf(root->left, a, b);
        if ((a <= root->key)  && (root->key <= b)) {
            print_unit(root);
        }
        tree_printf(root->right, a, b);
    }
    else if (a > b){
        if (root == NULL) return;
        tree_printf(root->right, a, b);
        if ((b <= root->key)  && (root->key <= a)) {
            print_unit(root);
        }
        tree_printf(root->left, a, b);
    }
}

unit* del_unit(unsigned int key, unit *root, int k, int* status) {
//    Поиск ключа
    unit *el = find_union(key, root);
    if (!el) {
        *status = -1;
        return root;
    }
//    Если есть несколько версий
    if (el->info->next){
        Info *inf1 = el->info;
        Info *inf2 = NULL;
        while ((inf1 != NULL) && (inf1->relise != k)){
            inf2 = inf1;
            inf1 = inf1->next;
        }
        if (inf1 == NULL) {
            *status = -2;
            return root;
        }
        if (inf2 == NULL){
            el->info = inf1->next;
            free(inf1);
            *status = 1;
            return root;
        }
        inf2->next = inf1->next;
        free(inf1->s);
        free(inf1);
        *status = 1;
        return root;
    }
    else if (el->info->relise != k){
        *status = -2;
        return root;
    }
//    Если это листок:
    if ((el->left == NULL) && (el->right == NULL) && (el != root)){
        if ((el->parent) && (el->parent->left == el)){
            el->parent->left = NULL;
        }
        else if (el->parent){
            el->parent->right = NULL;
        }
        if (el->next) el->next->previous = el->previous;
        if (el->previous) el->previous->next = el->next;
        free(el->info->s);
        free(el->info);
        free(el);
        *status = 1;
        return root;
    }
//    Если есть один дочерний узел

    if ((el != root) && ((el->left == NULL) || (el->right == NULL))){
        if ((el->parent) && (el->parent->left == el)){
            if (el->left == NULL){
                el->parent->left = el->right;
                if (el->right){
                    el->right->parent = el->parent;
                }
            }
            else{
                if (el->parent) el->parent->left = el->left;
                if (el->left){
                    el->left->parent = el->parent;
                }
            }
        }
        else{
            if (el->left == NULL){
                if (el->parent) {
                    el->parent->right = el->right;
                    if (el->right) {
                        el->right->parent = el->parent;
                    }
                }
            }
            else {
                if (el->parent) {
                    el->parent->right = el->left;
                    if (el->left) {
                        el->left->parent = el->parent;
                    }
                }
            }
        }
        if (el->next) el->next->previous = el->previous;
        if (el->previous) el->previous->next = el->next;
        free(el->info->s);
        free(el->info);
        free(el);
        *status = 1;
        return root;
    }
//    Если два дочерних узла
    unit* r = el->next;
    if (r == NULL){
        r = el->previous;
        if (r) {
            while ((r->left != NULL) && (r->right != NULL)) {
                r = r->previous;
            }
        }
        else {
            free(r);
            *status = 1;
            return NULL;
        }
    }
    else {
        while ((r->left != NULL) && (r->right != NULL)) {
            r = r->next;
        }
    }
        el->key = r->key;
//    free()
        *(el->info) = *(r->info);
        if (el != r->next) el->next = r->next;
        if (el != r->previous) el->previous = r->previous;
    if ((r->parent) && (r->parent->left == r)){
        if (r->left != NULL){
            r->parent->left = r->left;
            r->left->parent = r->parent;
        }
        else {
            r->parent->left = r->right;
            if (r->right){
                r->right->parent = r->parent;
            }
        }
    }
    else {
        if (r->left != NULL){
            if (r->parent) r->parent->right = r->left;
            r->left->parent = r->parent;
        }
        else {
            if (r->parent) r->parent->right = r->right;
            if (r->right){
                r->right->parent = r->parent;
            }
        }
    }
    if (r->next) r->next->previous = r->previous;
    if (r->previous) r->previous->next = r->next;
    if (r->parent == root) {
        free(r);
    } else {
        free(r->info);
        free(r);
    }
    *status = 1;
    return root;

}

unit* find_maxi(unsigned int key, unit *root){
//    5) Поиск элемента, соответствующего значению наибольшего ключа, не превышающего заданное значение. (если таких элементов несколько – действовать по аналогии с операцией поиска по ключу).
    unsigned int max = 0;
    unit* p = NULL;
    while (root != NULL){
        if (key > root->key){
            if (root->key >= max){
                max = root->key;
                p = root;
            }
            root = root->right;
        }
        else if (key < root->key){
            root = root->left;
        }
        else return root;
    }
    return p;
}

void tree_print_v3(unit* root, int lvl){
    if (root){
        tree_print_v3(root->left, lvl + 1);
        for (int i = 0; i < lvl; i++){
            printf("   ");
        }
        printf("%d\n", root->key);
        tree_print_v3(root->right, lvl + 1);
    }
}

void Time_tree(){
    unsigned int key[100000];
    unit* root = NULL;
    char* s = "a+b";
    int k;
    int i;
    int m = 0;
    FILE *f = fopen("time.csv", "w");
    clock_t t1, t2;
    srand(time(NULL));
//        Ключи для поиска
    for (i = 0; i < 100000; ++i){
        key[i] = rand() * rand();
    }
//        Делаем дерево
    for (int j = 1; j < 1000000; j += 1000){
        for (i = 0; i < 1000; ++i){
            k = rand() * rand();
            root = add_unit(k, s, root);
        }
        t1 = clock();
        for (i = 0; i < 100000; ++i){
            find_union(key[i], root);
        }
        t2 = clock();
        fprintf(f, "%d;%ld\n", m, t2 - t1);
        printf("number of nodes = %d, time = %ld\n", j, t2 - t1);
        m++;
    }
    fclose(f);
    tree_free(root);
}

void tree_free(unit* root){
    if (root){
        tree_free(root->left);
        tree_free(root->right);
        if (root->info){
            Info* inf1 = root->info;
            Info* inf2;
            while (inf1 != NULL){
                inf2 = inf1;
                inf1 = inf1->next;
                free(inf2->s);
                free(inf2);
            }
        }
        free(root);
    }
}

void graphviz_print(unit *root, FILE* f){
    if (root) {
        if (!root->parent) {
            fprintf(f, "digraph grapht {\n");
        }
        if (!root->left && !root->right){
            return;
        }
        if (root->left) {
            fprintf(f, "%d -> %d;\n", root->key, root->left->key);
            graphviz_print(root->left, f);
        }
        else {
            fprintf(f, "null%d[shape=point];\n", root->key);
            fprintf(f, "%d -> null%d;\n", root->key, root->key);
        }
        if (root->right) {
            fprintf(f, "%d -> %d;\n", root->key, root->right->key);
            graphviz_print(root->right, f);
        }
        else {
            fprintf(f, "null%d[shape=point];\n", root->key);
            fprintf(f, "%d -> null%d;\n", root->key, root->key);
        }
    }
}

void gr_print(unit* root){
    FILE *f = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\bufs1234567.txt", "w");
    graphviz_print(root, f);
    fprintf(f, "}");
    fclose(f);
    system("C:\\Users\\frunz\\Graphviz\\bin\\dot.exe -Tpng -o C:/Users/frunz/Desktop/c_or_c++/C/logs/test.png C:/Users/frunz/Desktop/c_or_c++/C/logs/bufs1234567.txt");
    system("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\test.png");
}