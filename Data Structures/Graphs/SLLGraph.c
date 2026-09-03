#include <stdlib.h>
#include <stdio.h>

struct Node{
    int item;

    struct Node *next;
};

struct List{
    struct Node *head;
    struct Node *tail;
};

struct List SLL_new(){
    struct List list;
    list.head = NULL;
    list.tail = NULL;\

    return list;
}

int SLL_empty(struct List *list){
    return list->head == NULL;
}

int SLL_length(struct List *list){
    struct Node *p;
    int count;

    count = 0;
    p = list->head;

    while(p != NULL){
        count++;
        p = p->next;
    }

    return count;
}

void SLL_append(struct List *list, int item){
    struct Node *node;

    node = malloc(sizeof(struct Node));
    node->next = NULL;
    node->item = item;

    if(SLL_empty(list)){
        list->head = node;
    }
    else{
        list->tail->next = node;
    }

    list->tail = node;
}

void SLL_push(struct List *list, int item){
    struct Node *node;
    
    node = malloc(sizeof(struct Node));
    node->next = list->head;
    node->item = item;

    list->head = node;

    if(SLL_empty(list)){
        list->tail = node;
    }
}

int SLL_pop(struct List *list){
    struct Node *node = list->head;
    int item;

    list->head = list->head->next;
    item = node->item;

    if(list->head == NULL)
        list->tail = NULL;

    free(node);

    return item;
}

void SLL_clear(struct List *list){    
    while(!SLL_empty(list)){
        SLL_pop(list);
    }
}

int SLL_contains(struct List *list, int item){
    struct Node *p;

    p = list->head;

    while(p != NULL){
        if(p->item == item)
            return 1;
        else
            p = p->next;
    }

    return 0;
}

struct Graph{
    struct List *vertices;
    int numVertices;
    int allocated;
};


struct Graph Graph_new(){
    struct Graph graph;
    graph.vertices = NULL;
    graph.numVertices = 0;
    graph.allocated = 0;

    return graph;
}

int Graph_empty(struct Graph *graph){
    return graph->vertices == NULL;
}

/*adds a vertex*/
void Graph_vertex(struct Graph *graph){
    graph->numVertices++;

    if(Graph_empty(graph)){
        graph->vertices = malloc(sizeof(struct List) * 10);

        if(graph->vertices == NULL){
            graph->numVertices--;
            printf("failed to add a new vertex");
            return;
        }

        graph->allocated = 10;
    }

    if(graph->allocated < graph->numVertices){
        struct List *listArray;
        graph->allocated += 10;

        listArray = realloc(graph->vertices, sizeof(struct List)*(graph->allocated));
        
        if(listArray == NULL){
            printf("failed to add a new vertex");
            graph->numVertices--;
            graph->allocated -= 10;

            return;
        }

        graph->vertices = listArray;
    }

    graph->vertices[graph->numVertices - 1].head = NULL;
    graph->vertices[graph->numVertices - 1].tail = NULL;
}

/*
adds an edge
vertex1 -> vertex2
*/
void Graph_edge(struct Graph *graph, int vertex1, int vertex2){
    SLL_append(graph->vertices+vertex1,vertex2);
}

int main(){
    struct Graph graph;
    graph = Graph_new();

    Graph_vertex(&graph);
    Graph_edge(&graph, 0, 0);

    printf("%i\n", SLL_contains(&graph.vertices[0],0));

    return 0;
}

