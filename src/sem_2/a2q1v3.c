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

int min_01(tree head, int k){
    int max=0;
    if(head==NULL){
        return 0;
    }
    int l=min_01(head->left, k);
    int r=min_01(head->right, k);
    if(l>r){
        max=l;
    } else{
        max=r;
    }
    if((max+1)%3==k){
       countmin++;
    }
    return max+1;
}

int check_prime(int n){
    int check=1;
    for(int i=2; i<n/2; i++){
        if(n%i==0){
            check=0;
            break;
        }
    }
    return check;
}

int inputs[3000005];
int main(){
    int n;
    int j=0;
    scanf("%d", &n);
    while(n>1){
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
    
    // int countmin=0;
    int hl=height(head->left)+1;
    int hr=height(head->right)+1;
    if(hl%3==0 || hr%3==0){
        min_00(head);
    } else{
        countmin++;
        if(hl%3==1){
            min_01(head->left, 1);
        } else if(hl%3==2){
            min_01(head->left, 2);
        }
        if(hr%3==1){
            min_01(head->right, 1);
        } else if(hr%3==2){
            min_01(head->right, 2);
        }
    }
    printf("%d\n", countmin);
    int primes[countmin];
    int y=0;
    while(y<primes){

    }
    return 0;
}