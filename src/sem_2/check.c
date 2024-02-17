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
int depth=0;
int min_01(tree head, int k, int ht){
    depth+=1;
    int max=0;
    if(head==NULL){
        return 0;
    }
    int l=min_01(head->left, k, ht);
    int r=min_01(head->right, k, ht);
    if(l>r){
        max=l;
    } else{
        max=r;
    }
    if((ht-(max+1))%3==0){
       countmin++;
    }
    return max+1;
}

int inputs[3000005];
int main(){
    int n;
    int j=0;
    scanf("%d", &n);

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
            }
            if(2*a+2<j){
                locations[a]->right=locations[2*a+2];
            }
            a++;
        }
    }

    tree head=locations[0];
    int hl=height(head->left)+1;
    int hr=height(head->right)+1;

    if(hl%3==0 && hr%3==0){
        min_00(head);
    } else if(hl%3==0 || hr%3==0){
        countmin++;
        if(hl%3==0){
            countmin+=hl/3;
            if(hr%3==1){
                min_01(head->right, 1, hr);
            } else if(hr%3==2){
                min_01(head->right, 2, hr);
            }
        } else{
            countmin+=hr/3;
            if(hl%3==1){
                min_01(head->left, 1, hl);
            } else if(hl%3==2){
                min_01(head->left, 2, hl);
            }
        }
    }
    else{
        countmin++;
        if(hl%3==1){
            min_01(head->left, 1, hl);
        } else if(hl%3==2){
            min_01(head->left, 2, hl);
        }
        if(hr%3==1){
            min_01(head->right, 1, hr);
        } else if(hr%3==2){
            min_01(head->right, 2, hr);
        }
    }

    printf("%d", countmin);
    return 0;
}