#include <stdio.h>
void main(){
    int n;
    scanf("%d",&n);
    int prime;
    int i;
    int num=1;
    for (i=1; i<=n; i++){
        for(int j=2; j<n; j++){
            if (num%j ==0){
                prime=0;
            }
            else{
                prime=1;
            }
        }
        if (prime ==1){
            printf("%d", i);
        }
        num+=1;
    }
}