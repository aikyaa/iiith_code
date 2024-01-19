#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    if(0 == n) {
        printf("0");
    } else {
        for(int i=30;i>=0; i--){
            if (((n>>i)&1)==1){
                for(int k=i; k>=0; k--){
                    printf("%d", (n>>k)&1);
                }
                printf("\n");
                break;
            }
        }
    }
}