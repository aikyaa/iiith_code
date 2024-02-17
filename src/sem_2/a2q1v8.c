#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int countmin=0;
int inputs[3000005];

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

int count_left(int t, int j){
    int count=0;
    int i,k;
    if(t!=0){
        i=7;
    } else{
        i=1;
    }
    while(i<j){
            k=i;
            while(k < 1.5*i+0.5){
                if(inputs[k]==1){
                    count+=1;
                }
                k++;
            }
            i=2*i+1;
            i=2*i+1;
            i=2*i+1;
        }
        return count;
}

int count_right(int t, int j){
    int count=0;
    int i,k;
    if(t!=0){
        i=7;
    } else{
        i=1;
    }
    while(i<j){
            k=(1.5)*i+0.5;
            while(k<(2*i+1)){
                if(inputs[k]==1){
                    count+=1;
                }
                k++;
            }
            i=2*i+1;
            i=2*i+1;
            i=2*i+1;
        }
        return count;
}

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
        countmin+=count_right(hr%3, j);
        countmin+=count_left(hl%3, j);
    } else if(hl%3==0 || hr%3==0){
        countmin++;
        if(hl%3==0){
            countmin+=hl/3;
            countmin+=count_right(hr%3, j);
        } else{
            countmin+=hr/3;
            countmin+=count_left(hl%3, j);
        }
    }
    else{
        countmin++;
        countmin+=count_left(hl%3, j);
        countmin+=count_right(hr%3, j);
    }

    printf("%d", countmin);
    return 0;
}