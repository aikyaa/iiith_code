#include <stdio.h>
int main(){
    int t;
    scanf("%d", &t);
    int n[t];
    int x[t][];
    int arr[t][];
    int max;
    int sum=0;
    for(int b=0;b<t;b++){
        scanf("%d", &n[b]);
        for(int a=1; a<=n[b]; a++){
            scanf("%d", &x[b][a]);
        }
    }
for(int c=0;c<t;c++){
    for(int i=1; i<=n[c]; i++){
        while(i<n[c]){
            sum+=x[c][i];
            i+=x[c][i];
        }
        arr[c][i]=sum;
        sum=0;
    }
    max=arr[c][1];
    for(int k=2; k<n[c]+1; k++){
        if (max<arr[c][k]){
            max=arr[c][k];
        }
    }
    printf("%d\n", max);
}
    return 0;
}