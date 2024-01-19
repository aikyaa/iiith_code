#include <stdio.h>
void main(){
    int arr[29];
    int n,temp;
    scanf("%d", &n);
    for(int j=0;j<=29;j++){
        if (n%2==1) {
            temp=j;
            break;
        }
    }
    for(int i=29; i>=0; i--){
        arr[i]=n%2;
        n/=2;
    }
    for (int k=0;k<30;k++){
        printf("%d", arr[k]);
    }

}