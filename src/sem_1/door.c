#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    int count[n+1];
    for(int l=0; l<(n-1);l++){
        count[l]=0;
    }
    for(int i=2;i<=n;i++){
        for(int j=1; j<=(n/i); j++){
            count[i*j]+=1;
        }
    }
    printf("1 ");
    for (int k=2; k<=n; k++){
        if (((count[k])%2)==0){
            printf("%d ", k);
        }
    }
}