#include <stdio.h>
#include <stdlib.h>
//change: using malloc to declare large arrays inside the main function
int main(){
    int t;
    int sum=0;
    int k;
    scanf("%d", &t);
    int n[t];
    int ** x = malloc(t*sizeof(int *));
    for(int z=0; z< t; z++){
        x[z] = malloc(200001*sizeof(int));
    }
    int max=0;
    int y=0;
    for(int a=0;a<t;a++){
       scanf("%d", &n[a]); 
       if (n[a]>y){
        y=n[a];
       }
       for(int b=1;b<=n[a]; b++){
         scanf("%d", &x[a][b]);
       }
    }
    int ** arr = malloc(t*sizeof(int *));
    for(int f=0; f< t; f++){
        arr[f] = malloc((y+1)*sizeof(int));
    }
    for(int c=0; c<t; c++){
        for(int i=1; i<n[c]+1; i++){
        k=i;
        while(i<=n[c]){
            sum+=x[c][i];
            i+=x[c][i];
        }
        i=k;
        arr[c][i]=sum;
        sum=0;
        }
        max=arr[c][1];
        for(int l=2; l<n[c]+1; l++){
            if (max<arr[c][l]){
                max=arr[c][l];
            }
        }
        printf("%d\n", max);
    }
    return 0;
}