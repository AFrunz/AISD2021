#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


/*(1) Добавление новой вершины в граф
 *(2) Добавление в граф нового ребра между двумя заданными вершинами, с необходимым вычислением веса ребра
 *(3) Удаление заданной вершины из графа; при этом удаляются и все ребра, связанные с удаляемой вершиной
 *(4) Удаление заданного ребра из графа
 *(5)Вывод ввиде списка смежностей
 *(12) Graphviz (есть)
 *(10) Загрузка из файла и запись в файл
 *(9) Случайная генерация графа
 *(6) Поиск некоторой заданной вершины из другой заданной вершины методом поиска в глубину
 * (если пути между вершинами нет, вернуть соответствующий код ошибки)
 *
 *7) Поиск кратчайшего пути между двумя заданными вершинами графа, используя алгоритм Беллмана — Форда
 *8) поиск минимального остовного дерева
 * результат - дерево, представленное ациклическим графом, с указанной вершиной в качестве корня). Результатом операции должен являться новый граф.
 *
 *
 *
 *
 *
 *
 *11) Таймирование
 *
 *
 *13) Поиск кратчайшего пути на карте (дает 1.65 балла)
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
    char* menu[] = {"0.Exit", "1.Add_node", "2.Add_edge", "3.Del_node", "4.Del_edge", "5.Deep_find",
                    "6.Min_way", "7.Min_ostov", "8.Print", "9.Graphviz", "10.Random_gen", "11.Time", "12.Clear"};
    int L = 13;
    int ok = 0;
    int flag = -2;
    Graph *head = NULL;
    while (flag != 0){
        if (flag == -2){
            printf("%s\n", "-1.Upload from file");
            for (int i = 0; i < L; i++){
                printf("%s\n", menu[i]);
            }
            scanf("%d%*c", &flag);
            continue;
        }
        if (flag == 1){
//            Добавление вершины
            float x, y;
            char* key;
            printf("Enter key\n");
            key = getString();
            printf("Enter x and y\n");
            scanf("%f %f", &x, &y);
            int status = add_node(&head, x, y, key);
            if (status == -1){
                printf("Error, key already exist\n");
            }
            else {
                printf("Success\n");
            }
        }
        else if (flag == 2){
//            Добавление ребра
            printf("Enter key1\n");
            char* key1 = getString();
            printf("Enter key2\n");
            char* key2 = getString();
            int status = add_edge(head, key1, key2);
            if (status == -1){
                printf("Key1 not found\n");
            }
            else if (status == -2){
                printf("Key2 not found\n");
            }
            else if (status == -3){
                printf("Edge already exist\n");
            }
            else {
                printf("Success\n");
            }

        }
        else if (flag == 3) {
//      Удаление узла
            char* key;
            printf("Enter key\n");
            key = getString();
            int status = del_node(&head, key);
            if (status == -1){
                printf("Error, key not found\n");
            }
            else {
                printf("Success\n");
            }
        }
        else if (flag == 4) {
//            Удаление ребра
            printf("Enter key1\n");
            char* key1 = getString();
            printf("Enter key2\n");
            char* key2 = getString();
            Graph* buf = Find_list(head, key1, NULL);
            int status = del_edge(buf, key2, 1);
            if (status == -1){
                printf("Key not found\n");
            }
            else {
                printf("Success\n");
            }
        }
        else if (flag == 5){
//      Поиск в глубину
            printf("Enter start key\n");
            char* key1 = getString();
            printf("Enter finish key\n");
            char* key2 = getString();
            deep_find(head, key1, key2);
        }
        else if (flag == 6){
//            Кратчайший путь
            printf("Enter start key\n");
            char* key1 = getString();
            printf("Enter finish key\n");
            char* key2 = getString();
            int status = min_way(head, key1, key2);
        }
        else if (flag == 7){
            printf("Enter start key\n");
            char* key1 = getString();
            Graph *ostov = min_ostov(head, key1);
            if (!ostov){
                printf("Error\n");
            }
            else {
                gr_print(ostov);
            }
        }
        else if (flag == 8){
            graph_print(head);
        }
        else if (flag == 9){
            gr_print(head);
        }
        else if (flag == 10){
            printf("Enter node number and edge number\n");
            int node, edge;
            scanf("%d %d", &node, &edge);
            head = random_graph(node, edge);
        }
        else if (flag == 11){
            int a;
        }
        else if (flag == 12){
            printf("Are you sure?\n1-y, 0-n\n");
            int status;
            scanf("%d", &status);
            if (status == 1){
                head = NULL;
            }
        }
        else if (flag == -1){
            head = file_read();
            ok = 1;
        }
        for (int i = 0; i < L; i++){
            printf("%s\n", menu[i]);
        }
        scanf("%d%*c", &flag);

    }
    if (ok){
        file_write(head);
    }
}




