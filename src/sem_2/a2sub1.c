#include <stdio.h>
#include <stdlib.h>

typedef struct treenode{
    int data;
    treenode* left;
    treenode* right;
}treenode;

typedef treenode* tree;

typedef struct stqueue{
    tree locations;
    int size;
    tree locationsrear;
}stqueue;

typedef stqueue* queue;

queue create_queue{
    queue Q;
    Q=(queue)malloc(sizeof(struct stqueue));
    Q->size=0;
    Q->locations=NULL;
    Q->locationsrear=NULL;
    return Q;
}

void push(queue Q,int x){
    tree new;
    new=(tree)malloc(sizeof(treenode));
    new->data=x;
    new->left=NULL;
    new->right=NULL;
    Q->locationsrear=new;
    if(Q->locations==NULL){
        Q->locations=new;
    }
    Q->size++;
}

void pop(queue Q){
    tree temp;
    temp=Q->locations;
    Q->locations
}

tree MakeNode(int x){
    tree T;
    T=(tree)malloc(sizeof(struct treenode));
    T->data=x;
    T->left=NULL;
    T->right=NULL;
    return T;
}

int main(){
    int n;
    tree T;
    scanf("%d", &n);
    int level_order[n];
    int height=1;
    int count=1;
    for(int i=0; i<n; i++){
        scanf("%d", &level_order[i]);
        count--;
        if(count==0){
            height=height*2;
            count=height;
            push(NULL);
        }
    }
    Q=create_queue();
    tree T;
    int j=0;
    T=MakeNode(level_order[j]);
    push(Q,level_order[j]);
    while(j<n){
        if(Q->locations==NULL){
            push(NULL);
            while()
        }
        else if(Q->locations->data==1){
            j++;
            if(level_order[j]==1){
                Q->locations->left=MakeNode(level_order[j]);
            }
            j++;
            if(level_order[j]==1){
                Q->locations->right=MakeNode(level_order[j]);
            }
        }
        pop(Q);
    }
    return 0;
}