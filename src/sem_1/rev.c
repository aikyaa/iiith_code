#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    int d4=(n%10);
    int d3=((n/10)%10);
    int d2=((n/100)%10);
    int d1=((n/1000)%10);
    printf("%d%d%d%d", d4, d3, d2, d1);
}