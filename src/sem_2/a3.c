#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _invalid -5555
#define bucket_count 32768

typedef struct stNode{
    int element;
    int index;
    struct stNode* next;    
}stNode;

typedef struct stNode* Node;
typedef int key;

typedef struct stht{
    int table_size;
    Node* category;    
}stht;

typedef struct stht* hasht;

int gethash(int value) {
    float c=(sqrt(5)-1)/2;
    long s = c*pow(2, 32);
    long sv = abs(s * value);
    int lower_sv = sv % (long) pow(2, 32);
    key k = lower_sv % bucket_count;
    return k;
}

hasht createht(int size){
    hasht newht=(hasht)malloc(sizeof(struct stht));
    // if(NULL==newht){
    //     printf("Out of memory");
    //     exit(0);
    // }
    newht->table_size=size;
    newht->category=(Node*)malloc(size*sizeof(Node));
    // if(NULL==newht->category){
    //     printf("Out of memory");
    //     exit(0);
    // }
    for(int i=0; i<size; i++){
        newht->category[i]=(Node)malloc(sizeof(struct stNode));
        // if(NULL==newht->category[i]){
        //     printf("Out of memory");
        //     exit(0);
        // }
        newht->category[i]->element=_invalid;
        newht->category[i]->index=_invalid;
        newht->category[i]->next=NULL;
    }
    return newht;
}

Node find(int target, hasht ht, int prev_index){
    key k=gethash(target);
    if(NULL==ht->category[k]){
        printf("Element not found");
        return NULL;
    }
    Node dup=ht->category[k];
    Node temp=NULL;
    while(NULL!=dup){
        if(target==dup->element && prev_index<dup->index){
            temp=dup;
        }
        if(dup->index<prev_index){
            break;
        }
        dup=dup->next;
    }
    return temp;
}

void delete(int target, hasht ht, int index){
    key k=gethash(target);
    if(NULL==ht->category[k]){
        printf("Element not found");
        return;
    }
    Node dup=ht->category[k];
    while(NULL!=dup){
        if(target==dup->element && index==dup->index){
            break;
        }
        dup=dup->next;
    }
    if (NULL!=dup && NULL!=dup->next){
        Node temp=dup->next;
        dup->next=dup->next->next;
        free(temp);
    }
}

void insert(int element, hasht ht, int index){
    key k=gethash(element);
    Node current_head=ht->category[k];
    //if(NULL==find(element,ht)){
        Node new_head=(Node)malloc(sizeof(struct stNode));
        // if(NULL==new_head){
        //     printf("Out of memory");
        //     exit(0);
        // }
        new_head->element=element;
        new_head->index= index;
        new_head->next=current_head;
        ht->category[k]=new_head;
    //}
}

int main(){
    int n;
    printf("%d  ", gethash(1));
    printf("%d  ", gethash(2));
    printf("%d  ", gethash(3));
    printf("%d  ", gethash(4));
    printf("%d  ", gethash(5));
    printf("%d  ", gethash(11));
    printf("%d  ", gethash(21));
    printf("%d  ", gethash(31));
    printf("%d  ", gethash(41));
    printf("%d  ", gethash(51));

    scanf("%d", &n);
    if(0==n){
        printf("0");
        return 0;
    }
    hasht ht=createht(bucket_count);
    int inputs[n];
    int indices[n];
    int largest_indices[n];
    for(int i=0; i<n; i++){
        scanf("%d", &inputs[i]);
        insert(inputs[i],ht, i);
        indices[i]=-1;
        largest_indices[i]=-1;
    }
    int largest_count=1;
    for(int j=0; j<n; j++){
        int count=1;
        indices[0]=j;
        for(int k=1; k<n-j; k++){
            Node temp=find(inputs[j]+(k),ht, indices[k-1]);
            if (NULL!=temp) {
                indices[k]=temp->index;
                count++;
            } else{
                break;
            }
        }

        if (largest_count<count) {
            largest_count=count;
            largest_indices[0]=j;
            for(int w=1; w<largest_count; w++){
                largest_indices[w]=indices[w];
            }
        }
        if(count==n){
            break;
        }
        //delete(inputs[j], ht, j);
    }

    printf("%d\n", largest_count);
    if(1==largest_count){
        printf("0");
        return 0;
    }
    for(int l=0; l<largest_count; l++){
        printf("%d ", largest_indices[l]);
    }
    return 0;
}