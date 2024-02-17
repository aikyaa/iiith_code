#include<stdlib.h>

void preorder(Bintree T){
    if(T==NULL){
        return;
    } 
    preorder(T->left);
    preorder(T->right);
    printf("%d", T->element);
    return;
}