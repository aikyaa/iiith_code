#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int k=0;

int largest_seq(int* inputs, int* desired, int n1, int n2, int* indices){
    if(n1==0||n2==0){
        return 0;
    } else{
        if(inputs[n1-1]==desired[n2-1]){
            indices[k]=n1-1;
            k++;
            return 1+largest_seq(inputs, desired, n1-1, n2-1, indices);
        } else{
            int case1=largest_seq(inputs,desired, n1-1, n2, indices);
            int case2=largest_seq(inputs, desired, n1, n2-1, indices);
            if (case1>case2){
                return case1;
            }else{
                return case2;
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);

    int* desired=(int*)malloc(1000000000*sizeof(int));
    for(int u=0; u<1000000000; u++){
        desired[u]=u+1;
    }

    int* indices=(int*)malloc(n*sizeof(int));

    int inputs[n];
    for(int l=0; l<n; l++){
        scanf("%d ", &inputs[n]);
    }

    int largest_length=largest_seq(inputs, desired, n, 1000000000, indices);
    printf("%d\n", largest_length);
    for(int v=0; v<largest_length; v++){
        printf("%d ", indices[v]);
    }
    return 0;
}