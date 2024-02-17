#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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
    int hasPhone=0;
    return new;
}

int check_neighbor(tree head){
    if (head==NULL) return 0;
    else return head->hasPhone;
}

int find_case(){
    find_case(head->left);
}

void findmin(tree head){
    if (head==NULL){
        return;
    }
    if(head->hasPhone==1){
        if(head->left!=NULL){
            findmin(head->left->left);
            findmin(head->left->right);
        }
        if (head->right!=NULL){
            findmin(head->right->left);
            findmin(head->right->right);
        }
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent)==0){
        head->hasPhone=1;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent)==0){
        head->hasPhone=1;
        countmin++;
        return;
    }
    if(check_neighbor(head->parent->parent)==0 && check_neighbor(head->parent)==0 && check_neighbor(head->left)==0 && check_neighbor(head->right)==0){
        head->hasPhone=1;
        countmin++;
        if(head->left!=NULL){
            findmin(head->left->left);
            findmin(head->left->right);
        }
        if (head->right!=NULL){
            findmin(head->right->left);
            findmin(head->right->right);
        }
    } else{
        findmin(head->left);
        findmin(head->right);
    }
    return;
}

void findmin2(tree head){
    if (head==NULL){
        return;
    }
    if(head->hasPhone==2){
        if(head->left!=NULL){
            findmin2(head->left->left);
            findmin2(head->left->right);
        }
        if (head->right!=NULL){
            findmin2(head->right->left);
            findmin2(head->right->right);
        }
        return;
    }
    if(head->right==NULL && head->left==NULL && check_neighbor(head->parent)!=2){
        head->hasPhone=2;
        countmin++;
        return;
    }
    if(head->right!=NULL && head->right->right==NULL && head->right->left==NULL && head->left!=NULL && head->left->left==NULL && head->left->right==NULL && check_neighbor(head->parent)==0){
        head->hasPhone=2;
        countmin++;
        return;
    }
    if(check_neighbor(head->parent->parent)!=2 && check_neighbor(head->parent)!=2 && check_neighbor(head->left)!=2 && check_neighbor(head->right)!=2){
        head->hasPhone=2;
        countmin++;
        if(head->left!=NULL){
            findmin2(head->left->left);
            findmin2(head->left->right);
        }
        if (head->right!=NULL){
            findmin2(head->right->left);
            findmin2(head->right->right);
        }
    } else{
        findmin2(head->left);
        findmin2(head->right);
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
    //finding count if root has phone
    root->hasPhone=1;
    countmin++;
    findmin(root);
    int v1=countmin;

    //finding count if root doesn't have phone
    if(root->left!=NULL || root->right!=NULL){
        countmin=0;
        if(root->left!=NULL){
            root->left->hasPhone=2;
            countmin++;
            findmin2(root->left->left);
            findmin2(root->left->right);
        }
        if(root->right!=NULL){
            root->right->hasPhone=2;
            countmin++;
            findmin2(root->right->left);
            findmin2(root->right->right);
        }
    }
    
    //finding min of the 2
    int min=0;
    if (v1<countmin) min=v1;
    else min=countmin;

    //output
    printf("%d", min);
    return 0;
}