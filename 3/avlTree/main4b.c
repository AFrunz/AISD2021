#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLtree.h"
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
char* getString(){
    int n, len, len_res = 0;
    char buf[51];
    char *res = NULL;
    do{
        n = scanf("%50[^\n]", buf);
        if (n < 0){
            if (!res) return NULL;
        }
        else if (n > 0) {
            len = (int)strlen(buf);
            len_res += len;
            res = realloc(res, (len_res + 1) * sizeof(char));
            memcpy(res + len_res - len, buf, len);
        }
        else{
            scanf("%*c");
        }
    } while (n > 0);
    if (len_res > 0){
        res[len_res] = '\0';
    }
    else {
        res = calloc(1, sizeof(char));
    }
    return res;
}

//    unit* r = find_next(root, el);
//    if (r == NULL){
//        r = find_previous(root, el);
//        if (r) {
//            while ((r->left != NULL) && (r->right != NULL)) {
//                r = find_previous(root, r);
//            }
//        }
//        else {
//            free(r);
//            *status = 1;
//            return NULL;
//        }
//    }
//    else {
//        while ((r->left != NULL) && (r->right != NULL)) {
//            r = find_next(root, r);
//        }
//    }
//    el->key = r->key;
////    free()
//    *(el->info) = *(r->info);
//    if ((r->parent) && (r->parent->left == r)){
//        if (r->left != NULL){
//            r->parent->left = r->left;
//            r->left->parent = r->parent;
//        }
//        else {
//            r->parent->left = r->right;
//            if (r->right){
//                r->right->parent = r->parent;
//            }
//        }
//    }
//    else {
//        if (r->left != NULL){
//            if (r->parent) r->parent->right = r->left;
//            r->left->parent = r->parent;
//        }
//        else {
//            if (r->parent) r->parent->right = r->right;
//            if (r->right){
//                r->right->parent = r->parent;
//            }
//        }
//    }
//    if (r->parent == root) {
//        free(r);
//    } else {
//        free(r->info);
//        free(r);
//    }
//    *status = 1;
//    return root;
//
//}
//
//
//void print_unit(unit *el) {
//    printf("%10u ", el->key);
//    Info *inf = el->info;
//    while (inf != NULL) {
//        printf("%10d %10s ",inf->relise, inf->s);
//        inf = inf->next;
//    }
//    printf("\n");
//}
//
//void tree_printf(unit* root, int a, int b){
////4) Вывод всего содержимого таблицы в заданном диапазоне значений ключей в указанном порядке их следования (a < key < b, (a, b) – прямой, (b, a) – обратный)
//    if (a < b){
//        if (root == NULL) return;
//        if ((a <= root->key)  && (root->key <= b)) {
//            print_unit(root);
//        }
//        tree_printf(root->left, a, b);
//        tree_printf(root->right, a, b);
//    }
//    else if (a > b){
//        if (root == NULL) return;
//        tree_printf(root->left, a, b);
//        tree_printf(root->right, a, b);
//        if ((b <= root->key)  && (root->key <= a)) {
//            print_unit(root);
//        }
//    }
//}
//// Печать от а до б(доработать немного
//
//unit* find_next(unit *x, unit *root){
////    Поиск следующего элемента
//    unit *ptr = NULL;
//    if (x->right != NULL){
//        ptr = x->right;
//        while (ptr->left != NULL){
//            ptr = ptr->left;
//        }
//        return ptr;
//    }
//    else {
//        ptr = x->parent;
//        while ((ptr != NULL) && (ptr->right == x)){
//            x = ptr;
//            ptr = x->parent;
//        }
//        return ptr;
//    }
//}
//// Поиск следующего элемента(ок)
//
//void del_unit();
//
//void tree_print_v3(unit* root, int lvl){
//    if (root){
//        tree_print_v3(root->left, lvl + 1);
//        for (int i = 0; i < lvl; i++){
//            printf("   ");
//        }
//        printf("%d\n", root->key);
//        tree_print_v3(root->right, lvl + 1);
//    }
//}
// Печать дерева(ок)

//int main(){
//    return 0;
//
//}


void menu(){

//    Чтение из файла
    char* menu[] = {"0.Exit", "1.Add", "2.Delete", "3.Find", "4.Print_less", "5.Find_dif",
                    "6.Print", "7. Time", "8. Graphviz"};
    int L = 9;
    printf("Upload tree from file? yes - 1, no - 0\n");
    int flag;
    int key;
    int f1, f2;
    unit* root = NULL;
    scanf("%d%*c", &flag);
    if (flag == 1){
        printf("Enter file name\n");
        char* filename = getString();
        FILE *f = fopen(filename, "r");
        while (f == NULL) {
            printf("Error, file is not exist, repeat\n");
            free(filename);
            filename = getString();
            f = fopen(filename, "r");
        }
        while (!feof(f)){
            char* s = (char*)calloc(100, sizeof(char));
            Info* inf = (Info*)calloc(1, sizeof(Info));
            fscanf(f, "%d", &key);
            fscanf(f, "%d %d %s", &f1, &f2, s);
            inf->s = s;
            inf->f1 = f1;
            inf->f2 = f2;
            add_unit(&root, key, inf);
        }
        fclose(f);
    }
    flag = -1;
    char* inf = NULL;
    int vers;
    while (flag != 0){
        if (flag == -1){
            for (int i = 0; i < L; i++){
                printf("%s\n", menu[i]);
            }
            scanf("%d", &flag);
            continue;
        }
        if (flag == 1){
            printf("Enter key\n");
            scanf("%d", &key);
            printf("Enter f1, f2 and s\n");
            scanf("%d %d", &f1, &f2);
            inf = getString();
            Info* k = (Info*)calloc(1, sizeof(Info));
            k->f1 = f1;
            k->f2 = f2;
            k->s = inf;
            Info* b = add_unit(&root, key, k);
            if (!b) printf("Success\n");
            else printf("Information updated, old info: %d %d %s", b->f1, b->f2, b->s);
        }
        else if (flag == 2){
            printf("Enter key\n");
            scanf("%d", &key);
            int res;
            root = del_unit(key, root, &res);
            if (res == -1) printf("Element not fond\n");
            if (res == 1) printf("Success\n");
        }
        else if (flag == 3) {
            printf("Enter key\n");
            scanf("%d", &key);
            unit *res = find_union(key, root);
            if (res == NULL) printf("Element not found\n");
            else {
                printf("%10d %10d %10d %10d %10s\n", res->key, res->balance,res->info->f1, res->info->f2, res->info->s);
            }
        }
        else if (flag == 4) {
            int fl;
            printf("Enter key\n");
            scanf("%d", &key);
            print_max(root, key, 0);
        }
        else if (flag == 5){
            printf("Enter key\n");
            scanf("%d", &key);
            unit* j = max_dif(root, key);
            if (j) {
                printf("%10d %10d %10d %10d %10s\n", j->key, j->balance, j->info->f1, j->info->f2, j->info->s);
            }
        }
        else if (flag == 6){
            tree_print_v3(root, 0);
        }
        else if (flag == 7){
            Time_tree();
        }
        else if (flag == 8){
            gr_print(root);
        }
        for (int i = 0; i < L; i++){
            printf("%s\n", menu[i]);
        }
        scanf("%d", &flag);

    }
    tree_free(root);
//    file_printf(root);

}







//}

int main(){
    menu();
    return 0;
}



//int main(){
//    Info* inf = (Info*)calloc(1, sizeof(Info));
//    inf->s = "abc";
//    inf->f1 = 1;
//    inf->f2 = 3;
//    unit* root = NULL;
//    int flag = 4;
////    add_unit(&root, 1, inf);
////    add_unit(&root, 4, inf);
////    add_unit(&root, -2, inf);
////    add_unit(&root, -3, inf);
////    add_unit(&root, 6, inf);
////    add_unit(&root, 7, inf);
////    add_unit(&root, 8, inf);
////    add_unit(&root, 9, inf);
////    add_unit(&root, 5, inf);
//    add_unit(&root, 50, inf);
//    add_unit(&root, 40, inf);
//    add_unit(&root, 45, inf);
//    add_unit(&root, 30, inf);
//    add_unit(&root, 80, inf);
//    add_unit(&root, 90, inf);
//    add_unit(&root, 95, inf);
//    add_unit(&root, 85, inf);
//    add_unit(&root, 60, inf);
//    add_unit(&root, 70, inf);
//    add_unit(&root, 55, inf);
//    add_unit(&root, 52, inf);
//    int a;
//    tree_print_v3(root, 0);
//    printf("\n\n");
//    root = del_unit(45, root, 0, &a);
//    tree_print_v3(root, 0);
////    right_turn(&root, root);
////    tree_print_v3(root, 0);
////    left_turn(&root, root->right->right);
////    tree_print_v3(root, 0);
//    return 0;
//}


