#include <stdio.h>
void main(){
    int n;
    int x;
    x=0b(1);
    scanf("%d", &n);
    for(int k=30; k>=0; k--){
    printf("%d", (n>>=k)&1);
    }
}