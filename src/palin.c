#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int arr[N];
    int count=0;
    for (int i=0; i<N; i++){
        scanf(" %d", &arr[i]);
    }
    int l=0;
    for (int j=0; j<N; j++){
        for (int k=j+1; k<N; k++){
            while((j+l)<=(k-l)){
            if (arr[j+l]==arr[k-l]) {
                l+=1;               
            } else{
                break;
            }
            count+=1;
            }
        }
    }
    printf("%d", count+N);
}