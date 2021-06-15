#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"


//(1+) Включение нового элемента в таблицу без нарушения свойств упорядоченности;(есть)
//2) Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы
//(3+-) Поиск информации по заданному ключу; если элементов с одинаковым ключем может быть несколько, указывается порядковый номер искомого элемента; возврат осуществлять при помощи указателя, возврат копий элементов не допускается.
//(4+) Вывод всего содержимого таблицы в заданном диапазоне значений ключей в указанном порядке их следования (a < key < b, (a, b) – прямой, (b, a) – обратный).
//(5+) Поиск элемента, соответствующего значению наибольшего ключа, не превышающего заданное значение. (если таких элементов несколько – действовать по аналогии с операцией поиска по ключу).
//
//
//


//unit *find_min(unit *root){
////    Поиск минимального элемента дерева
//    unit *ptr = root;
//    if (ptr == NULL){
//        return NULL;
//    }
//    while (ptr->left != NULL){
//        ptr = ptr->left;
//    }
//    return ptr;
//}

//unit* find_maj(unit* root, unsigned int key){
//    unit* min = find_min(root);
//
//    return min;
//}

//void tree_print(unit* root, unit** u, int *lvl){
//    if (root != NULL){
//        tree_print(root->left, u, lvl);
//        tree_print(root->right, u, lvl);
//        u[*lvl] = root;
//        *lvl = *lvl + 1;
//        return;
//    }
//    u[*lvl] = NULL;
//    *lvl = *lvl + 1;
//}

//
//int lens(unit* root, int len){
//    if (root == NULL) return len;
//    int a1 = lens(root->left, len + 1);
//    int a2 = lens(root->right, len + 1);
//    if (a2 >= a1) return a2;
//    return a1;
//
//
//}

//char* str_plus_strt(char* s1, int k1, char* s2, int k2){
//    char* s = (char*)calloc(123, sizeof(char));
//    char* p = s;
//    for (int i = 0; i < k1; i++, s++){
//        *s = *s1;
//    }
//    for (int i = 0; i < k2; i++, s++){
//        *s = *s2;
//    }
//    return s;
//}

//
//void tree_print_v2(unit* root, int lvl_v, int lvl_h, FILE* f){
//    if (root != NULL) {
//        fseek(f, 0, 0);
//        char *buf = calloc(1000, sizeof(char));
//        int buf_int;
//        for (int i = 0; i < lvl_v; i++) {
//            fscanf(f, "%[\n]", buf);
//        }
//        for (int i = 0; i < lvl_h; i++) {
//            fscanf(f, "%d", &buf_int);
//        }
//        fprintf(f, "---%d", root->key);
//        tree_print_v2(root->left, lvl_v, lvl_h + 1, f);
//        tree_print_v2(root->right, lvl_v + 1, lvl_h + 1, f);
//    }
//    fseek(f, 0, 0);
//    char *buf = calloc(1000, sizeof(char));
//    int buf_int;
//    for (int i = 0; i < lvl_v; i++) {
//        fscanf(f, "%[\n]", buf);
//    }
//    for (int i = 0; i < lvl_h; i++) {
//        fscanf(f, "%d", &buf_int);
//    }
//    fprintf(f, "\n");
//}

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

void menu(){
    char* menu[] = {"0.Exit", "1.Add", "2.Delete", "3.Find", "4.Find_max", "5.Find_section",
                    "6.Print", "7. Graphviz"};
    int L = 8;
    printf("Upload tree from file? yes - 1, no - 0\n");
    int flag;
    unsigned int key;
    char* info = (char*)calloc(100, sizeof(char));
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
            fscanf(f, "%u", &key);
            fscanf(f, "%s", info);
            char* info2 = (char*)calloc(strlen(info) + 1, sizeof(char));
            strcpy(info2, info);
            root = add_unit(key, info2, root);
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
            printf("Enter key and info\n");
            scanf("%u", &key);
            inf = getString();
            root = add_unit(key, inf, root);
            printf("Success\n");
        }
        else if (flag == 2){
            printf("Enter key and version\n");
            scanf("%u %d", &key, &vers);
            int res;
            root = del_unit(key, root, vers, &res);
            if (res == -1) printf("Element not fond\n");
            if (res == -2) printf("Element with this version not found\n");
            if (res == 1) printf("Success\n");
        }
        else if (flag == 3){
            printf("Enter key\n");
            scanf("%u", &key);
            unit* res = find_union(key, root);
            if (res == NULL) printf("Element not found\n");
            else {
                if (res->info->next != NULL) {
                    printf("Enter version\n");
                    scanf("%d", &vers);
                    Info *inform = find_inf(res, vers);
                    if (inform == NULL) printf("Element not found\n");
                    else {
                        printf("%10u %10d %10s\n", res->key, inform->relise, inform->s);
                    }
                } else{
                    printf("%10u %10d %10s\n", res->key, res->info->relise, res->info->s);
                }
            }
        }
        else if (flag == 4){
            printf("Enter key\n");
            scanf("%u", &key);
            unit* res = find_maxi(key, root);
            if (res == NULL) printf("Element not found\n");
            else {
                if (res->info->next != NULL){
                    printf("Enter version\n");
                    scanf("%d", &vers);
                    Info *inform = find_inf(res, vers);
                    if (inform == NULL) printf("Element not found\n");
                    else {
                        printf("%10u %10d %10s\n",res->key, inform->relise, inform->s);
                    }
                }
                else if (vers == 0){
                    printf("%10u %10d %10s\n",res->key, res->info->relise, res->info->s);
                }
                else printf("Element not found\n");
            }
        }
        else if (flag == 5){
            printf("Enter a and b\n");
            int a, b;
            scanf("%d %d", &a, &b);
            tree_printf(root, a, b);
        }
        else if (flag == 6){
            tree_print_v3(root, 0);
        }
        else if (flag == 9){
            print_next(root);
        }
        else if (flag == 7){
            gr_print(root);
        }
        else if (flag == 8){
            Time_tree();
        }
        for (int i = 0; i < L; i++){
            printf("%s\n", menu[i]);
        }
        scanf("%d", &flag);

    }
    tree_free(root);
//    file_printf(root);

}


int main(){
    menu();
//    unit* root = NULL;
//    unit* r = NULL;
//    int a = 0;
//    unit* u[1000];
//    root = add_unit(9, "inf1", root);
//    root = add_unit(11, "inf1", root);
//    root = add_unit(2, "inf1", root);
//    root = add_unit(1, "inf1", root);
//    root = add_unit(3, "inf1", root);
//    root = add_unit(0, "inf1", root);
//    root = add_unit(4, "inf1", root);
//    root = add_unit(22, "inf1", root);
//    tree_print_v3(root, 0);
//    del_unit(9, &root, 0);
//    printf("\n\n\n\n\n");
//    tree_print_v3(root, 0);
    return 0;
}
