#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int countmin=0;
typedef struct treenode{
    int data;
    struct treenode* left;
    struct treenode* right;
}treenode;

typedef treenode* tree;

tree MakeNode(int x){
    tree new;
    new=(tree)malloc(sizeof(treenode));
    new->data=x;
    new->left=NULL;
    new->right=NULL;
    return new;
}

int height(tree head){
    int max=0;
    if(head==NULL){
        return 0;
    }
    int l=height(head->left);
    int r=height(head->right);
    if(l>r){
        max=l;
    } else{
        max=r;
    }
    return max+1;
}

int min_00(tree head){
    int max=0;
    if(head==NULL){
        return 0;
    }
    int l=min_00(head->left);
    int r=min_00(head->right);
    if(l>r){
        max=l;
    } else{
        max=r;
    }
    if((max+1)%3==2){
       countmin++;
    }
    return max+1;
}

int min_01(tree head){
    int max=0;
    if(head==NULL){
        return 0;
    }
    int l=min_01(head->left);
    int r=min_01(head->right);
    if(l>r){
        max=l;
    } else{
        max=r;
    }
    if((max+1)%2==0){
       countmin++;
    }
    return max+1;
}

int main(){
    int n;
    int j=0;
    scanf("%d", &n);
    tree locations[n];
    for(int i=0;i<n;i++){
        int temp;
        scanf("%d", &temp);
        if(temp==1){
            locations[i]=MakeNode(1);
        } else{
            locations[i]=NULL;
        }
    }
    while(j<n){
        if(locations[j]==NULL){
            j++;
        } else{
            if(2*j+1<n){
                locations[j]->left=locations[2*j+1];
            }
            if(2*j+2<n){
                locations[j]->right=locations[2*j+2];
            }
            j++;
        }
    }
    tree head=locations[0];
    // int countmin=0;
    int hl=height(head->left)+1;
    int hr=height(head->right)+1;
    if(hl%3==0 && hr%3==0){
        min_00(head);
    } else{
        min_01(head);
    }
    printf("%d", countmin);
    return 0;
}