#include <stdio.h>
void main(){
    int n,i;
    scanf("%d", &n);
    int num=3;
    int prime;
    printf("2 ");
    for(i=1; i<=n; i++){
        for(int j=2; num<n; j++){
            prime=1;
            if (num % j==0){
                prime=0;
                break;
            }
        }
        if (prime!=0){
            printf("%d ",num);
        }
        num+= 1;
    }
}
//this program won't print 2, it shouldn't print 1 but it does