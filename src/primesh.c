#include <stdio.h>

void main(){
    int  n,i;
    scanf("%d",&n);
    int prime =0;
    
    
    printf("2  ");
    for(int i=3;i<=n;i++)
    {
        for (int j=2; j<i;j++){
            if(i%j==0){
                prime = 1;
                break;
            }
        }
        if(prime == 0){
           printf("%d   ", i);
       }
       prime = 0;
    }
}