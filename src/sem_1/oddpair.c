#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int l=0;l<n;l++){
    scanf(" %d", &arr[l]);
    }
    int x=0;
    for(int i=0;i<n;i++){
        x=x^arr[i];
    }
    printf("%d", x);
}