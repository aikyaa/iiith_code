#include <stdio.h>
#include <math.h>

void main(){
    int n,temp,k,x;
    x=pow(2,k-1);
    scanf("%d", &n);
    for(int k=30; k>0; k--){
        if (((n%x)%2)==1){
            temp=k;
            break;
        }
    }
    printf("%d", temp);
    /*for(k=temp; k>0; k--){
        printf("%d", (n/x)%2);
    }*/
}