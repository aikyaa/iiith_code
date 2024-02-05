#include <stdio.h>
#include <stdlib.h>

typedef struct treenode{
    int data;
    treenode* left;
    treenode* right;
}treenode;

typedef treenode* Bintree;

Bintree MakeNode(int x){
    Bintree T;
    T=(Bintree)malloc(sizeof(struct treenode));
    T->data=x;
    T->left=NULL;
    T->right=NULL;
    return T;
}

Bintree Insert(Bintree T, int x, int height, int count){
    Bintree root=T;
    while(height>1){
        if(count<=height){
            if(T->left!=NULL){
                T=T->left;
            } else if(T->right!=NULL){
                T=T->right;
            }
        } else{
            if(T->right!=NULL){
                T=T->right;
            } else if(T->left!=NULL){
                T=T->left;
            }
        }
    }
    if(T->left==NULL){
        T->left=MakeNode(x);
    }
    else if(T->right==NULL){
        T->right=MakeNode(x);
    }
    return root;
}

int main(){
    int n;
    Bintree T;
    scanf("%d", &n);
    int level_order[n];
    int height=1;
    int count=1;
    for(int i=0; i<n; i++){
        scanf("%d", &level_order[i]);
        if(level_order[i]==1){
            T=Insert(T,1,height, count);
        }
        count--;
        if(count==0){
            height=height*2;
            count=height;
        }
    }

    return 0;
}