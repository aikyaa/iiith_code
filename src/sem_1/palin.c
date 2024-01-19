#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int arr[N];
    int count=0;
    for (int i=0; i<N; i++){
        scanf(" %d", &arr[i]);
    }
    int value=1;
    for (int j=0; j<N; j++){
        for (int k=j+1; k<N; k++){
            for(int l=0; l<=(k-j)/2; l++){
                if (arr[j+l]!=arr[k-l]){
                    value=0;
                    break;
                }
            }
            if (value!=0){
                count+=1;
            }
            value=1;
        }
    }
    printf("%d", count+N);
}