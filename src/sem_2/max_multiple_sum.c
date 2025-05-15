#include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    for(int a=0; a<t; a++){
        int n;
        scanf("%d", &n);
        int max_sum_key=2;
        int max_sum=0;
        for(int i=2; i<=n; i++){
            int sum=0;
            for(int j=0; i*j<=n; j++){
                sum+=i*j;
            }
            if(sum>max_sum){
                max_sum=sum;
                max_sum_key=i;
            }
        }
        printf("%d", max_sum_key);
    }
}