#include <stdio.h>
int main(){
    int n;
    scanf("%d", &n);
    int x[n+1];
    int arr[n+1];
    for(int a=1; a<=n; a++){
        scanf("%d", &x[a]);
    }
    int sum=0;
    int k;
    for(int i=1; i<n+1; i++){
        k=i;
        while(i<=n){
            sum+=x[i];
            i+=x[i];
        }
        i=k;
        arr[i]=sum;
        sum=0;
    }
    int max=arr[1];
    for(int l=2; l<n+1; l++){
        if (max<arr[l]){
            max=arr[l];
        }
    }
    printf("%d", max);
    return 0;
}