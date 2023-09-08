#include <stdio.h>
#include <math.h>

void main(){
    int n,temp,k,x;
    scanf("%d", &n);
    for(int k=30; k>0; k--){
        x=pow(2,k-1);
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