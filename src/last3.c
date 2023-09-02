#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    printf("%d %d %d",((n/4)%2),((n/2)%2),n%2);
}