#include<stdlib.h>

typedef int element;

typedef struct stNode{
    element data;
    struct stNode* next;
}stNode;

typedef stNode* Node;

typedef struct stqueue{
    Node Front;
    Node Rear;
    int size;
}stqueue;

typedef stqueue* Queue;

Queue CreateQueue(int max_elements){
    Queue Q;
    Q=(Node)malloc(sizeof(struct stNode));
    Q->Front=NULL;
    Q->Rear=NULL;
    Q->size=0;
    return Q;
}

void enqueue(Queue Q, element x){
    Node new;
    new=(Node)malloc(sizeof(stNode));
}