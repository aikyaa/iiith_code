#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <math.h>

int countmin=0;
int inputs[3000005];

typedef struct treenode{
    struct treenode* parent;
    struct treenode* left;
    struct treenode* right;
    int hasPhone;
}treenode;

typedef treenode* tree;

tree MakeNode(int x){
    tree new;
    new=(tree)malloc(sizeof(treenode));
    new->parent=NULL;
    new->left=NULL;
    new->right=NULL;
    new->hasPhone=0;
    return new;
}

int check_neighbor(tree node, int k){
    if(node==NULL){
        return 0;
    }
    if(node->hasPhone==k){
        return 1;
    }
    // if(node->left!=NULL && node->left->hasPhone==k){
    //     return 1;
    // }
    // if(node->parent!=NULL && node->parent->hasPhone==k){
    //     return 1;
    // }
    // if(node->right!=NULL && node->right->hasPhone==k){
    //     return 1;
    // }
    return 0;
}

void findmin(tree head){
    if (head==NULL){
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent,1)==0&& check_neighbor(head,1)==0){
        head->parent->hasPhone=1;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent,1)==0&& check_neighbor(head,1)==0){
        head->hasPhone=1;
        countmin++;
        return;
    }
    findmin(head->left);
    findmin(head->right);
    if(head->hasPhone==1){
        return;
    }
    if(check_neighbor(head->parent->parent,1)==0&&check_neighbor(head->parent,1)==0 && check_neighbor(head->left,1)==0 && check_neighbor(head->right,1)==0){
        head->hasPhone=1;
        countmin++;
    }
    return;
}

void findmin3(tree head){
    
    if (head==NULL){
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent,3)==0&& check_neighbor(head,3)==0){
        head->parent->hasPhone=3;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent,3)==0&& check_neighbor(head, 3)==0){
        head->hasPhone=3;
        countmin++;
        return;
    }
    findmin3(head->left);
        findmin3(head->right);
    if(head->hasPhone==3){
        return;
    }
    if(check_neighbor(head->parent->parent,3)==0&&check_neighbor(head->parent,3)==0 &&check_neighbor(head->left,3)==0 && check_neighbor(head->right,3)==0){
        head->hasPhone=3;
        countmin++;
    }
    return;
}

void findmin4(tree head){
    if (head==NULL){
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent,4)==0&& check_neighbor(head,4)==0){
        head->parent->hasPhone=4;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent,4)==0&& check_neighbor(head,4)==0){
        head->hasPhone=4;
        countmin++;
        return;
    }
    findmin4(head->left);
    findmin4(head->right);
    if(head->hasPhone==4){
        return;
    }
    if(check_neighbor(head->parent->parent,4)==0&&check_neighbor(head->parent,4)==0 && check_neighbor(head->left,4)==0 && check_neighbor(head->right,4)==0&& check_neighbor(head,4)==0){
        head->hasPhone=4;
        countmin++;
    }
    return;
}

void findmin5(tree head){
    if (head==NULL){
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent,5)==0&& check_neighbor(head,5)==0){
        head->parent->hasPhone=5;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent,5)==0&& check_neighbor(head,5)==0){
        head->hasPhone=5;
        countmin++;
        return;
    }
    findmin5(head->left);
    findmin5(head->right);
    if(head->hasPhone==5){
        return;
    }
    if(check_neighbor(head->parent->parent,5)==0&&check_neighbor(head->parent,5)==0 && check_neighbor(head->left,5)==0 && check_neighbor(head->right,5)==0&& check_neighbor(head,5)==0){
        head->hasPhone=5;
        countmin++;
    }
    return;
}

void findmin2(tree head){
    if (head==NULL){
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent,2)==0&& check_neighbor(head,2)==0){
        head->parent->hasPhone=2;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent,2)==0&& check_neighbor(head,2)==0){
        head->hasPhone=2;
        countmin++;
        return;
    }
    findmin2(head->left);
    findmin2(head->right);
    if(head->hasPhone==2){
        return;
    }
    if(check_neighbor(head->parent->parent,2)==0&&check_neighbor(head->parent,2)==0 && check_neighbor(head->left,2)==0 && check_neighbor(head->right,2)==0){
        head->hasPhone=2;
        countmin++;
    }
    return;
}

int main(){
    int n;
    int j=0;
    scanf("%d", &n);

    //edge cases
    if(n==0){
        countmin=0;
        printf("0");
        return 0;
    } else if(n==1){
        scanf("%d", &inputs[0]);
        countmin=inputs[0];
        printf("%d", inputs[0]);
        return 0;
    }

    //converting input array to proper level order and finding num of elements j
    while(n>0){
        if(inputs[j]==0){
            n--;
            scanf("%d", &inputs[j]);
            if(inputs[j]==0){
                inputs[j]=-1;
                inputs[2*j+1]=-1;
                inputs[2*j+2]=-1;
            }   
        } else if(inputs[j]==-1){
            inputs[2*j+1]=-1;
            inputs[2*j+2]=-1;
        }
        j++;
    }

    //creating tree
    tree locations[j];
    for(int i=0;i<j;i++){
        if(inputs[i]==1){
            locations[i]=MakeNode(1);
        } else{
            locations[i]=NULL;
        }
    }
    int a=0;
    while(a<j){
        if(locations[a]==NULL){
            a++;
        } else{
            if(2*a+1<j){
                locations[a]->left=locations[2*a+1];
                if (locations[2*a+1]!=NULL)
                    locations[2*a+1]->parent=locations[a];
            }
            if(2*a+2<j){
                locations[a]->right=locations[2*a+2];
                if (locations[2*a+2]!=NULL)
                    locations[2*a+2]->parent=locations[a];
            }
            a++;
        }
    }
    tree root=locations[0];

    if(root->left==NULL && root->right==NULL){
        printf("1");
        return 0;
    }
    //finding count if root has phone
    root->hasPhone=1;
    countmin++;
    findmin(root);
    int v1=countmin;
    int v2=0;
    int v3=0;
    int v4=0;
    int out_min=v1;
    
    //finding count if root doesn't have phone
    if(root->left!=NULL && root->right!=NULL){
        countmin=0;
        if(root->left!=NULL){
            root->left->hasPhone=2;
            countmin++;
            findmin2(root->left->left);
            findmin2(root->left->right);
        }
        if(root->right->left==NULL && root->left->right==NULL){
            root->right->hasPhone=2;
            countmin++;
        }
        findmin2(root->right->left);
        findmin2(root->right->right);
        v2=countmin;
        if(v2<out_min) out_min=v2;

        countmin=0;
        if(root->right!=NULL){
            root->right->hasPhone=4;
            countmin++;
            findmin4(root->right->left);
            findmin4(root->right->right);
        }
        if(root->left->left==NULL && root->left->right==NULL){
            root->left->hasPhone=4;
            countmin++;
        }
        findmin4(root->left->left);
        findmin4(root->left->right);
        v4=countmin;
        if(v4<out_min) out_min=v4;
    }

    countmin=0;
        if(root->left!=NULL && root->right==NULL){
            root->left->hasPhone=3;
            countmin++;
            findmin3(root->left->left);
            findmin3(root->left->right);
            v3=countmin;
    if(v3<out_min) out_min=v3;

        }
    
    int v5=0;
    countmin=0;
        if(root->right!=NULL && root->left==NULL){
            root->right->hasPhone=5;
            countmin++;
            findmin5(root->right->left);
            findmin5(root->right->right);
            v5=countmin;
        if(v5<out_min) out_min=v5;
        }

    //output
    printf("%d", out_min);
    return 0;
}