#include <stdio.h>
void main(){
    int n;
    scanf("%d", &n);
    int arr[n];
    for(int l=0;l<n;l++){
    scanf(" %d", &arr[l]);
    }
    int count=0;
    for (int i=0;i<n;i++){
        for(int j=1;j<n;j++){
            if(arr[i]==arr[j]){
                count+=1;
            }
        }
        if (count%2!=0){
            printf("%d", arr[i]);
            break;
        }
        count=0;
    }
}