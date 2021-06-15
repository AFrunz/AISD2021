#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Graph.h"
#include "queue.c"

//Переделать очередь, сделать через кучу


Graph* Find_list(Graph* head, char* key, Graph** prev){
    Graph* p = head;
    Graph* pr = NULL;
    while (p){
        if (strcmp(p->key, key) == 0 ){
            if (prev){
                (*prev) = pr;
            }
            return p;
        }
        pr = p;
        p = p->next;
    }
    return NULL;
}

//Добавление узла, -1 если узел с таким именем существует;
int add_node(Graph** head, float x, float y, char* key){
    if (Find_list(*head, key, NULL)) return -1;

    if (!*head){
        *head = (Graph*)calloc(1, sizeof(Graph));
        (*head)->x = x;
        (*head)->y = y;
        (*head)->key = key;
        return 0;
    }

    Graph *p = (Graph*)calloc(1, sizeof(Graph));
    p->x = x;
    p->y = y;
    p->key = key;
    p->k = (*head)->k + 1;
// Проверитб
    p->next = *head;
    (*head) = p;
    return 0;
}

// Удаление узла, -1 если узел не найден; флаг 1 если нужно удалить ребро с двух сторон
int del_edge(Graph* g, char* key, int flag){
    edge* b = NULL;
    if (!g) return -1;
    edge* e = g->edge;
    while (e){
        if (strcmp(e->node->key, key) == 0){
            if (!b){
                g->edge = e->next;
                if (flag){
                    del_edge(e->node, g->key, 0);
                }
                free(e);
                return 0;
            }
            else {
                if (flag) {
                    del_edge(e->node, g->key, 0);
                }
                b->next = e->next;
                free(e);
                return 0;
            }
        }
        b = e;
        e = e->next;
    }
    return -1;
}

// Добавление ребра, -1 если не найден 1 ключ, -2 если не найден второй ключ, -3 если ребро уже существует;
int add_edge(Graph* head, char* key1, char* key2){
    Graph* g1 = Find_list(head, key1, NULL);
    if (!g1) return -1;
    Graph* g2 = Find_list(head, key2, NULL);
    if (!g2) return -2;
    if (strcmp(key1, key2) == 0) return -4;
    edge* p1 = g1->edge;
    edge* p2 = NULL;
    while (p1){
        if (strcmp(p1->node->key, key2) == 0) return -3;
        p1 = p1->next;
    }

    p1 = (edge*)calloc(1, sizeof(edge));
    p1->node = g2;
    float weight = sqrtf((g2->x - g1->x)*(g2->x - g1->x) + (g2->y - g1->y)*(g2->y - g1->y));
    p1->weight = weight;
    p1->next = g1->edge;
    g1->edge = p1;
    p2 = (edge*)calloc(1, sizeof(edge));
    p2->node = g1;
    p2->weight = weight;
    p2->next = g2->edge;
    g2->edge = p2;
    return 0;
}

// Удаление узла, -1 если узел не найден
int del_node(Graph** head, char* key){
    Graph* prev = NULL;
    Graph* p = Find_list(*head, key, &prev);
    if (!p) return -1;
    edge* e = p->edge;
    edge* e1 = e;
    while (e){
        del_edge(e->node, p->key, 0);
        e1 = e;
        e = e->next;
        free(e1);
    }
    if (p == *head){
        (*head) = p->next;
        free(p);
        return 0;
    }
    prev->next = p->next;
    free(p);
    return 0;
}

// Вывод графа через консоль
void graph_print(Graph* head){
    printf("%10s %10s %10s\n", "key", "x", "y");
    while (head){
        printf("%10s %10f %10f ", head->key, head->x, head->y);
        edge* buf = head->edge;
        while (buf){
            printf("-> %s(%0.2f) ", buf->node->key, buf->weight);
            buf = buf->next;
        }
        printf("\n");
        head = head->next;
    }
}

// Вывод графа графвиз
void gr_print(Graph* head){
    FILE *f = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\bufs1234567.txt", "w");

    fprintf(f, "graph grapht {\n");
    Graph* buf = head;
    Graph* buf1 = NULL;
    while (buf){
        fprintf(f, "\"%s\";\n", buf->key);
        edge* t = buf->edge;
        while (t){
            buf1 = head;
            int flag = 0;
            while (buf1 != buf){
                if (buf1 == t->node) {
                    flag = 1;
                    break;
                }
                buf1 = buf1->next;
            }
            if (flag != 1) {
                fprintf(f, "\"%s\"--\"%s\"[label=\"%0.2f\"];\n", buf->key, t->node->key, t->weight);
            }
            t = t->next;
        }
        buf = buf->next;
    }


    fprintf(f, "}");
    fclose(f);
    system("C:\\Users\\frunz\\Graphviz\\bin\\dot.exe -Tpng -o C:/Users/frunz/Desktop/c_or_c++/C/logs/test.png C:/Users/frunz/Desktop/c_or_c++/C/logs/bufs1234567.txt");
    system("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\test.png");
}

char* fgetString(FILE* f){
    int n, len, len_res = 0;
    char buf[51];
    char *res = NULL;
    do{
        n = fscanf(f, "%50[^\n]", buf);
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
            fscanf(f, "%*c");
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

// Чтение из файла
Graph* file_read(){
    FILE *f = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\graph_node.txt", "r");
    FILE *g = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\graph_edge.txt", "r");
    Graph* head = NULL;
    if (!f){
        printf("Node file is empty or not exist\n");
        return NULL;
    }
    else {
        while (!feof(f)) {
            char *s = fgetString(f);
            if (!s) break;
            float x, y;
            fscanf(f, "%f %f%*c", &x, &y);
            add_node(&head, x, y, s);
        }
    }
    fclose(f);
    if (!g){
        printf("Edge file is empty or not exist\n");
        return NULL;
    }
    else {
        while (!feof(g)) {
            char *s = fgetString(g);
            if (!s) break;
            int k;
            fscanf(g, "%d%*c", &k);
            for (int i = 0; i < k; i++){
                char* s1 = fgetString(g);
                add_edge(head, s, s1);
                free(s1);
            }
            free(s);
        }
    }
    fclose(g);
    return head;
}

// Запись в файл
void file_write(Graph* head){
    FILE *f = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\graph_node.txt", "w");
    FILE *g = fopen("C:\\Users\\frunz\\Desktop\\c_or_c++\\C\\logs\\graph_edge.txt", "w");
    Graph *p = head;
    while (p){
        fprintf(f, "%s\n%f %f\n", p->key, p->x, p->y);
        edge *q = p->edge;
        fprintf(g, "%s\n", p->key);
        int k = 0;
        while (q){
            k++;
            q = q->next;
        }
        fprintf(g, "%d\n", k);
        q = p->edge;
        while (q){
            fprintf(g, "%s\n", q->node->key);
            q = q->next;
        }
        p = p->next;
    }
}

int deep_f(Graph* el, char* finish, int* color, Graph_list* res){

    if (!el) return -1;
    color[el->k] = 1;
    edge* buf = el->edge;
    while (buf){
        if (strcmp(buf->node->key, finish) == 0){
            res->l[res->k] = buf->node;
            res->k = res->k + 1;
            return 1;
        }
        if (color[buf->node->k] == 0) {
            int status = deep_f(buf->node, finish, color, res);
            if (status == 1){
                res->l[res->k] = buf->node;
                res->k = res->k + 1;
                return 1;
            }
        }
        buf = buf->next;
    }
    color[el->k] = 2;
    return 0;
}

// Поиск в глубину
void deep_find(Graph* head, char* start, char* finish){
    if (!head) return;
    if (strcmp(start, finish) == 0){
        printf("The same keys\n");
        return;
    }
    int *color = (int*)calloc(head->k + 1, sizeof(int));
    Graph_list *res = (Graph_list*)calloc(1, sizeof(Graph_list));
    res->l = (Graph**)calloc(head->k + 1, sizeof(Graph*));
    Graph* el = Find_list(head, start, NULL);
    int status = deep_f(el, finish, color, res);
    if (status == 1){
        printf("%s ", el->key);
        for (int i = 0; i < res->k; i++){
            printf("%s ", res->l[res->k - i - 1]->key);
        }
        printf("\n");
    }
    else {
        printf("Not found\n");
    }

}


// Минимальный путь
int min_way(Graph* head, char* start, char* finish){
    if (!head) return -1;
    if (strcmp(start, finish) == 0){
        printf("The same keys\n");
        return -1;
    }
    float *d = (float*)calloc(head->k + 1, sizeof(float));
    Graph** res = (Graph**)calloc(head->k + 1, sizeof(Graph*));
    Graph* el = Find_list(head, start, NULL);
    if (!el) return -1;
    Graph* fin = Find_list(head, finish, NULL);
    if (!fin) return -1;
    for (int i = 0; i < head->k + 1; i++){
        d[i] = -1;
    }
    d[el->k] = 0;
    for (int i = 0; i < head->k; i++){
        Graph* buf = head;
        for (int j = 0; j < head->k + 1; j++){
            edge* buf1 = buf->edge;
            while (buf1){
                if ((d[buf1->node->k] == -1) && (d[buf->k] != -1)){
                    d[buf1->node->k] = d[buf->k] + buf1->weight;
                    res[buf1->node->k] = buf;
                }
                else if ((d[buf1->node->k] != -1) && (d[buf->k] != -1) && (d[buf1->node->k] > d[buf->k] + buf1->weight)){
                    d[buf1->node->k] = d[buf->k] + buf1->weight;
                    res[buf1->node->k] = buf;
                }
                buf1 = buf1->next;
            }
            buf = buf->next;
            if (!buf) break;
        }
    }
    Graph *buf = fin;
    if (d[fin->k] != -1){
        printf("%f\n",d[fin->k]);
        do {
            printf("%s ", fin->key);
            fin = res[fin->k];
        }while ((res[fin->k]) && res[fin->k] != buf);
        printf("%s\n", el->key);
    }
    else{
        printf("Have no way\n");
        return -1;
    }
    return 0;
}



Graph* random_graph(int node_count, int edge_count){
    srand(time(NULL));
    Graph *head = NULL;
    if (node_count <= 0){
        node_count = 1;
    }
    char** d = (char**)calloc(node_count + 1, sizeof(char*));
    char* q = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < node_count; i++){
        char* s = (char*)calloc(6, sizeof(char));
        d[i] = s;
        int j;
        for (j = 0; j < 4; j++){
            int t= abs(rand()*rand()*rand())%26;
            s[j] = *(q + t);
        }
        s[j] = '\0';
        float x = rand() % 50;
        float y = rand()% 50;
        add_node(&head, x, y, s);
    }
    for (int i = 0; i < node_count; i++){
        for (int j = 0; j < edge_count; j++){
            int r = abs(rand()) % node_count;
            add_edge(head, d[i], d[r]);
        }
    }
    free(d);
    return head;

}

Graph* min_ostov(Graph* g, char* key_){
    Graph *check = g;
    while (check){
        if (!check->edge) return NULL;
        check = check->next;
    }


    Graph *r = Find_list(g, key_, NULL);
    if (!g || !r) return NULL;
    Queue* q = Queue_init();
    float* key = (float*)calloc(g->k + 1, sizeof(int));
    Graph** par = (Graph**)calloc(g->k + 1, sizeof(Graph));
    for (int i = 0; i < g->k + 1; i++){
        key[i] = (float)INT_MAX;
    }
    key[r->k] = 0;
    Graph *buf = g;
    QueueUp_write(q, r, key);
    while (buf){
        if (buf != r){
            QueueUp_write(q, buf, key);
        }
        buf = buf->next;
    }
    Queue_print(q);
    while (q->head){
        Graph* u = NULL;
        Queue_read(q, &u);
        if (!u) break;
        edge* buf2 = u->edge;
        while (buf2){
            if ((QueueUp_find(q, buf2->node, key, NULL) != NULL) && (buf2->weight < key[buf2->node->k])){
                par[buf2->node->k] = u;
                key[buf2->node->k] = buf2->weight;
                Change_list(q, key, buf2->node, buf2->weight);
                Queue_print(q);
            }
            buf2 = buf2->next;
        }
    }
    Graph* h = NULL;
    Graph* buf3 = g;
    while (buf3){
        add_node(&h, buf3->x, buf3->y, buf3->key);
        buf3 = buf3->next;
    }
    buf3 = g;
    while (buf3){
        if (par[buf3->k]) {
            add_edge(h, buf3->key, par[buf3->k]->key);
        }
        buf3 = buf3->next;
    }
    return h;
}

//
//void graph_time(){
//    int step = 10;
//    int max = 250;
//    int iter = 1000;
//    for (int i = 1; i < max; i += step){
//        Graph* gr = random_graph(i, i / 5);
//
//
//
//
//
//    }
//
//}



