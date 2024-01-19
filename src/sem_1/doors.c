#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    if (n==0){
        printf("0");
    } else {
    for(int i=1; (i*i)<=n; i++){
        printf("%d ", i*i);
    }
}
}