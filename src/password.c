#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    int possibilities=(((10-n)*(10-n-1))*3);
    printf("%d", possibilities);
}