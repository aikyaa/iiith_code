#include <stdio.h>
void main(){
    int n;
    int prime=1;
    scanf("%d", &n);
    printf("2 ");
    for(int i=3;i<=n;i+=2){
        for(int j=2; j<i;j++){
        if (i%j==0){
            prime=0;
            break;
        }
        }
        if (prime!=0){
            printf("%d ", i);
        }
        prime=1;

    }
}