#ifndef C_GRAPH_H
#define C_GRAPH_H

typedef struct Graph Graph;

// Список связей графа
typedef struct edge {
    struct edge* next;
    float weight;
    Graph* node;
}edge;

// Узел графа
struct Graph{
    int k;
    char* key;
    float x;
    float y;
    edge* edge;
    struct Graph* next;
};

typedef struct Graph_list{
    Graph** l;
    int k;
}Graph_list;


int add_node(Graph** head, float x, float y, char* key);

int add_edge(Graph* head, char* key1, char* key2);

int del_node(Graph** head, char* key);

int del_edge(Graph* g, char* key, int flag);

Graph* Find_list(Graph* head, char* key, Graph** prev);

void deep_find(Graph* head, char* start, char* finish);

int min_way(Graph* head, char* start, char* finish);

void graph_print(Graph* head);

void gr_print(Graph* head);

Graph* random_graph(int node_count, int edge_count);

void file_write(Graph* head);

Graph* file_read();

Graph* min_ostov(Graph* g, char* key_);


#endif //C_GRAPH_H
