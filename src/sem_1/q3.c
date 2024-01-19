#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int color_code;
    struct Node* next;
} Node;
typedef Node* LinkedList;
LinkedList append(int code, LinkedList head) {
    Node* D = (Node *) malloc(sizeof(Node));
    D->color_code = code;
    D->next = NULL;
    if (head == NULL) {
        return D;
    }
    Node* temp=head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = D;
    return head;
}
void print_list(LinkedList l) {
    while (l!= NULL&& l->next!=NULL) {
        printf("%d -> ",l->color_code);
        l = l->next; 
    }
    printf("%d", l->color_code);
}
void main(){
    int n;
    scanf("%d", &n);
    int colors[n];
    LinkedList l= NULL;
    for(int i=0; i<n; i++){
        scanf("%d", &colors[i]);
    }
    for(int j=0; j<n; j++){
        l=append(colors[j], l);
    }
    Node *temp = l;
    Node *dup = NULL;
    while(temp != NULL && temp->next != NULL){
        if(temp->color_code == temp->next->color_code) {
            dup = temp->next;
            temp->next=dup->next;
            free(dup);
            dup = NULL;
        }
        temp = temp->next;
    }
    print_list(l);    
}