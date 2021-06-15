#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AVLtree.h"
#include <time.h>

/* (1) Включение нового элемента в таблицу (есть)
 * (если информация с заданным ключом уже есть, то изменяется значение информационного поля, а старое возвращается в качестве результата)
 * 2) Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы
 * (3) Поиск информации по заданному ключу; возврат осуществлять при помощи указателя, возврат копий элементов не допускается. (есть)
 * (4) Вывод всего содержимого таблицы в прямом порядке следования ключей, не превышающих заданный
 * (если ключ не указан - вывод всей таблицы) (есть)
 * (5) Поиск элемента, наиболее отличающегося по значению ключа от заданного ключа (есть)
 * (6) Форматированный вывод (есть)
 * 7) Чтение из файла
 * 8) Таймирование
 * (9) Очистка памяти
 */






void tree_print_v3(unit* root, int lvl){
    if (root){
        tree_print_v3(root->right, lvl + 1);
        for (int i = 0; i < lvl; i++){
            printf("   ");
        }
        printf("%d(%d)\n", root->key, root->balance);
//        if (root->parent) printf("%d(%d)\n", root->key, root->parent->key);
//        else printf("%d(NULL)\n", root->key);
        tree_print_v3(root->left, lvl + 1);
    }
}

unit* right_turn(unit** root, unit* el, int flag) {
    unit *buf = NULL;
    unit* b = NULL;
    if (!el->left) return NULL;
    b = el->left;
//    1. Поменяем родителя
    if (flag){
        el->balance = 0;
        el->left->balance = 0;
    }
    if (el->parent){
        if (el->parent->left == el){
            el->parent->left = el->left;
        }
        else {
            el->parent->right = el->left;
        }
        el->left->parent = el->parent;
    }
    else{
        *root = el->left;
        el->left->parent = NULL;
    }
//    2. Элемент вверх!


    buf = el->left->right;
    el->left->right = el;
    el->parent = el->left;
    el->left = buf;
    if (buf) buf->parent = el;
    return b;
//    tree_print_v3(*root, 0);
//    printf("right  %d\n\n\n", el->key);
}

unit* left_turn(unit** root, unit* el, int flag){
    unit* buf = NULL;
    unit*b = NULL;
    if (!el->right) return NULL;
    b = el->right;
    if (flag) {
        el->balance = 0;
        el->right->balance = 0;
    }
//    1. Поменяем родителя
    if (el->parent){
        if (el->parent->left == el){
            el->parent->left = el->right;
        }
        else {
            el->parent->right = el->right;
        }

        el->right->parent = el->parent;
    }
    else{
        if (el->right->left) el->right->left->parent = *root;
        *root = el->right;
        el->right->parent = NULL;
    }
//    2. Элемент вверх!
    buf = el->right->left;
    el->right->left = el;
    el->parent = el->right;
    el->right = buf;
    if (buf) buf->parent = el;
    return b;
//    tree_print_v3(*root, 0);
//    printf("left  %d\n\n\n", el->key);
}

unit* bigRightTurn(unit** root, unit* p1, unit* p2){
    unit* buf = p1->right;
    if (p1->right->balance == -1) {
        p1->right->balance = 0;
        p1->balance = 0;
        p2->balance = 1;
    }
    else if (p1->right->balance == 1){
        p1->right->balance = 0;
        p1->balance = -1;
        p2->balance = 0;
    }
    else if (p1->right->balance == 0){
        p1->right->balance = 0;
        p1->balance = 0;
        p2->balance = 0;
    }
    left_turn(root, p1, 0);
    right_turn(root, p2, 0);
    return buf;
}

unit* bigLeftTurn(unit** root, unit* p1, unit* p2){
    unit* buf = p1->left;
    if (p1->left->balance == -1) {
        p1->left->balance = 0;
        p2->balance = 0;
        p1->balance = 1;
    }
    else if (p1->left->balance == 1){
        p1->left->balance = 0;
        p1->balance = 0;
        p2->balance = -1;
    }
    else if (p1->left->balance == 0){
        p1->left->balance = 0;
        p1->balance = 0;
        p2->balance = 0;
    }
    right_turn(root, p1, 0);
    left_turn(root, p2, 0);
    return buf;
}

unit *target(unit *root, int key){
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

Info* add_unit(unit**root, int key, Info *info){
///1) Включение нового элемента в таблицу без нарушения свойств упорядоченности;
    unit* ptr1 = NULL;
    unit* ptr2 = NULL;
//    tree_print_v3(*root, 0);
//    printf("\n\n\n");
//    Если дерева еще нет
    if (!*root){
        (*root) = (unit*)calloc(1, sizeof(unit));
        (*root)->info = (Info*)calloc(1, sizeof(Info));
        (*root)->key = key;
        *((*root)->info) = *(info);
        (*root)->info->s = (char*)malloc(sizeof(char) * (strlen(info->s) + 1));
        strcpy((*root)->info->s, info->s);
        return NULL;
    }
    else {
//        Поиск места
        ptr1 = target(*root, key);
        ptr2 = ptr1;
//        Вставка вправо
        if (key > ptr1->key) {
            ptr1->right = (unit *) calloc(1, sizeof(unit));
            ptr1 = ptr1->right;
//            Вставка влево
        } else if (key < ptr1->key) {
            ptr1->left = (unit *) calloc(1, sizeof(unit));
            ptr1 = ptr1->left;
        }
//        Если элемент уже существует
        else {
            Info* buf = (*root)->info;
            (*root)->info = info;
            return buf;
        }
//        Добавление информации
        ptr1->info = (Info*)calloc(1, sizeof(Info));
        ptr1->key = key;
        ptr1->parent = ptr2;
        *(ptr1->info) = *(info);
        ptr1->info->s = (char*)malloc(sizeof(char) * (strlen(info->s) + 1));
        strcpy(ptr1->info->s, info->s);
        int lorr = 0;
        while ((ptr2 != NULL)) {
            if (ptr2->left == ptr1) {
                lorr = -1;
                ptr2->balance -= 1;
            }
            else {
                lorr = 1;
                ptr2->balance += 1;
            }
            if (ptr2->balance == 0) break;
//            Проверяем, нужна ли балансировка
            if (abs(ptr2->balance) == 2){

                if ((lorr == 1) && (ptr1->balance >= 0)){
                    left_turn(root, ptr2, 1);
                    break;
                }
                else if ((lorr == -1) && (ptr1->balance <= 0)){
                    right_turn(root, ptr2, 1);
                    break;
                }
                else if ((lorr == 1) && (ptr1->balance < 0)) {
                    bigLeftTurn(root, ptr1, ptr2);
                    break;
                }
                else {
                    bigRightTurn(root, ptr1, ptr2);
                    break;
                }


            }

            ptr1 = ptr2;
            ptr2 = ptr2->parent;

        }




    }
    return NULL;
}

unit* find_union(int key, unit *root){
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

unit* find_next(unit* root, unit* x){
    if (x->right){
        x = x->right;
        while (x->left){
            x = x->left;
        }
        return x;
    }
    else{
        while (x->parent && (x->parent->right == x)){
            x = x->parent;
        }
        if (x->parent) return x->parent;
        return x;
    }
}

unit* find_previous(unit* root, unit* x){
    if (x->left){
        x = x->left;
        while (x->right){
            x = x->right;
        }
        return x;
    }
    else{
        while (x->parent && (x->parent->left == x)){
            x = x->parent;
        }
        if (x->parent) return x->parent;
        return x;
    }

}

unit* correct(unit* p, unit*x, unit** root, int lorr){
    unit* buf = NULL;
            if ((lorr == 1) && (x->balance >= 0)){
                buf = left_turn(root, p, 1);
                return buf;
            }
            else if ((lorr == -1) && (x->balance <= 0)){
                buf = right_turn(root, p, 1);
                return buf;
            }
            else if ((lorr == 1) && (x->balance < 0)) {
                buf = bigLeftTurn(root, x, p);
                return buf;
            }
            else {
                buf = bigRightTurn(root, x, p);
                return buf;
            }
}


void bal(unit* x, unit** root){
    int lorr;
    unit* p = x->parent;
    while (p) {
        if (p->left == x) {
            p->balance += 1;
            lorr = -1;
        } else {
            p->balance -= 1;
            lorr = 1;
        }
        if (p->balance > 1) {
            x = correct(p, p->right, root, 1);
            p = x->parent;
        } else if (p->balance < -1) {
            x = correct(p, p->left, root, -1);
            p = x->parent;
        } else if (abs(p->balance) == 1) {
            return;
        } else{
            x = p;
            p = p->parent;
        }
    }

}

unit* del_unit_one(unit* root, unit* el){
        if ((el->parent) && (el->parent->left == el)) {
            if (el->left == NULL) {
                el->parent->left = el->right;
                if (el->right) {
                    el->right->parent = el->parent;
                }
            } else {
                if (el->parent) el->parent->left = el->left;
                if (el->left) {
                    el->left->parent = el->parent;
                }
            }
        } else {
            if (el->left == NULL) {
                if (el->parent) {
                    el->parent->right = el->right;
                    if (el->right) {
                        el->right->parent = el->parent;
                    }
                }
            } else {
                if (el->parent) {
                    el->parent->right = el->left;
                    if (el->left) {
                        el->left->parent = el->parent;
                    }
                }
            }
        }
//        free(el->info->s);
//        free(el->info);
//        free(el);
        return root;
    }



unit* del_unit(int key, unit *root, int* status) {
//    Поиск ключа
    unit *el = find_union(key, root);
    if ((el == root) && (!el->left) && (!el->right)) {
        *status = 1;
        return NULL;
    }
    if (!el) {
        *status = -1;
        return root;
    }
    //    Если это листок:
    if ((el->left == NULL) && (el->right == NULL) && (el != root)) {
        bal(el, &root);
        if ((el->parent) && (el->parent->left == el)) {
            el->parent->left = NULL;
        } else if (el->parent) {
            el->parent->right = NULL;
        }
        free(el->info->s);
        free(el->info);
        free(el);
        *status = 1;
        return root;
    }

//    Если есть один дочерний узел
    if ((el != root) && ((el->left == NULL) || (el->right == NULL))) {
        bal(el, &root);
        if ((el->parent) && (el->parent->left == el)) {
            if (el->left == NULL) {
                el->parent->left = el->right;
                if (el->right) {
                    el->right->parent = el->parent;
                }
            } else {
                if (el->parent) el->parent->left = el->left;
                if (el->left) {
                    el->left->parent = el->parent;
                }
            }
        } else {
            if (el->left == NULL) {
                if (el->parent) {
                    el->parent->right = el->right;
                    if (el->right) {
                        el->right->parent = el->parent;
                    }
                }
            } else {
                if (el->parent) {
                    el->parent->right = el->left;
                    if (el->left) {
                        el->left->parent = el->parent;
                    }
                }
            }
        }
        free(el->info->s);
        free(el->info);
        free(el);
        *status = 1;
        return root;
    }

//    Если два дочерних узла

    unit *r = el->right;
    if (r){
        while (r->left) {
            r = r->left;
        }
    }
    else{
        r = el->left;
        if (!r) return NULL;
        while (r->right){
            r = r->right;
        }
    }
    bal(r, &root);
    el->key = r->key;
    free(el->info->s);
    free(el->info);
    el->info = r->info;

    if (!r->left && !r->right) {
        if (r->parent->left == r) {
            r->parent->left = NULL;
        } else {
            r->parent->right = NULL;
        }
    }
    else {
        if ((r->parent) && (r->parent->left == r)) {
            if (r->left == NULL) {
                r->parent->left = r->right;
                if (r->right) {
                    r->right->parent = r->parent;
                }
            } else {
                if (r->parent) r->parent->left = r->left;
                if (r->left) {
                    r->left->parent = r->parent;
                }
            }
        } else {
            if (r->left == NULL) {
                if (r->parent) {
                    r->parent->right = r->right;
                    if (r->right) {
                        r->right->parent = r->parent;
                    }
                }
            } else {
                if (r->parent) {
                    r->parent->right = r->left;
                    if (r->left) {
                        r->left->parent = r->parent;
                    }
                }
            }
        }
    }
    free(r);
    *status = 1;
    return root;
}

void print_max(unit* root, int key, int flag){
    if (root){
        if (root->key <= key || flag){
            printf("%10d %10d %10s %10d %10d\n", root->key, root->balance, root->info->s, root->info->f1, root->info->f2);
        }
        print_max(root->left, key, flag);
        print_max(root->right, key, flag);
    }
}

unit* max_dif(unit* root, int key){
    unit* min = root;
    while (min->left){
        min = min->left;
    }
    unit* max = root;
    while (max->right){
        max = max->right;
    }
    if (abs(key - min->key) > abs(key - max->key)) return min;
    return max;
}

void tree_free(unit* root){
    if (root){
        tree_free(root->left);
        tree_free(root->right);
        free(root->info->s);
        free(root->info);
        free(root);
    }

}


void Time_tree(){
    int key[100000];
    unit* root = NULL;
    char* s = "a+b";
    Info* inf = (Info*)calloc(1, sizeof(Info));
    inf->s = s;
    inf->f1 = 1;
    inf->f2 = 2;
    int k;
    int i;
    int m = 0;
    FILE *f = fopen("time1.csv", "w");
    clock_t t1, t2;
    srand(time(NULL));
//        Ключи для поиска
    for (i = 0; i < 100000; ++i){
        key[i] = rand() * rand();
    }
//        Делаем дерево
    for (int j = 1; j < 1000000; j += 10000){
        for (i = 0; i < 10000; ++i){
            k = rand() * rand();
            add_unit(&root, k, inf);
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


