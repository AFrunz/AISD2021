#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Heap.h"
#define N 100


/*(1)Включение нового элемента в таблицу без нарушения свойств упорядоченности
 *(2)Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы
 * если элементов несколько, то указывается номер удаляемого элемента).
 *(3)Поиск информации по заданному ключу
 *(4)Вывод всего содержимого таблицы в заданном диапазоне значений ключей в указанном порядке их следования
 * (a < key < b, (a, b) – прямой, (b, a) – обратный).
 *(5)Поиск элемента, соответствующего значению наибольшего ключа, не превышающего заданное значение.
 * (если таких элементов несколько – действовать по аналогии с операцией поиска по ключу).
 *(6) Вывод в виде массива
 *(7) Вывод ввиде дерева
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


int main(){
    char* menu[] = {"0.Exit", "1.Add", "2.Delete", "3.Find", "4.Find_max", "5.Find_section",
                    "6.Print", "7.Graphviz"};
    int L = 8;
    printf("Upload tree from file? yes - 1, no - 0\n");
    int flag;
    unsigned int key;
    char* info = (char*)calloc(100, sizeof(char));
    Tree* root = init_tree(N);
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
            add_unit(root, key, info2);
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
            int status = add_unit(root, key, inf);
            if (status == -1) printf("Table is full\n");
            else printf("Success\n");
        }
        else if (flag == 2){
            printf("Enter key and version\n");
            scanf("%u %d", &key, &vers);
            int status = del_unit(root,key, vers);
            if (status == -1) printf("Key not exist\n");
            else if (status == -2) printf("Version not exist\n");
            else if (status == 0) printf("Success\n");
        }
        else if (flag == 3){
            printf("Enter key\n");
            scanf("%u", &key);
            int status = find_unit(root, key);
            if (status == -1) printf("Key not exist\n");
            else if (root->unit[status]->inf->next) {
                printf("Enter version\n");
                scanf("%d", &vers);
                Info* buf = root->unit[status]->inf;
                int fl = 0;
                while (buf){
                    if (buf->relise == vers){
                        printf("%u %s\n",root->unit[status]->key, buf->s);
                        fl = 1;
                        break;
                    }
                    buf = buf->next;
                }
                if (fl == 0) printf("Version not found\n");
            }
            else printf("%u %s\n",root->unit[status]->key, root->unit[status]->inf->s);
        }
        else if (flag == 4){
            printf("Enter key\n");
            scanf("%u", &key);
            Unit* status = find_max(root, key);
            if (status){
                if (status->inf->next){
                    printf("Enter version\n");
                    scanf("%d", &vers);
                    Info* buf = status->inf;
                    int fl = 0;
                    while (buf){
                        if (buf->relise == vers){
                            printf("%u %s\n",status->key, buf->s);
                            fl = 1;
                            break;
                        }
                        buf = buf->next;
                }
                    if (fl == 0) printf("Version not found\n");
                }
                else {
                    printf("%u %s\n",status->key, status->inf->s);
                }
            }
        }
        else if (flag == 5){
            printf("Enter a and b\n");
            int a, b;
            scanf("%d %d", &a, &b);
            conditional_print(root, a, b);
        }
        else if (flag == 6){
            array_print(root);
        }
        else if (flag == 7){
            tree_print(root);
        }
        for (int i = 0; i < L; i++){
            printf("%s\n", menu[i]);
        }
        scanf("%d", &flag);

    }
    return 0;
}