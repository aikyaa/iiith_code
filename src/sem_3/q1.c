#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long int element;

typedef struct setnode{
    long long int value;
    int idx;
} set;

typedef set* node;

int cmp(const void* a, const void* b ){
    set* s1=(set *)a;
    set* s2= (set *)b;
    return s1->value-s2->value;
}

int main(){
int t;
scanf("%d", &t);
int n=0;
node arr;
for(int i=0; i<t;i++){
    scanf("%d", &n);
    arr=(node)malloc(n* sizeof(set));
    for(int j=0; j<n; j++){
        long long int var=0;
        scanf("%lld ", &var);
        arr[j].value=var;
        arr[j].idx=j;
    }
    qsort(arr,n,sizeof(set),cmp);
    element time=0;
    for(int k=0; k<n; k++){
        time+=arr[k].value;
        if (k<n-1){
            if (arr[k].idx>arr[k+1].idx) time+=(arr[k].idx-arr[k+1].idx);
            else time+= arr[k+1].idx-arr[k].idx;
        }
        printf("%lld\t", time);
    }
    printf("%lld\n", time);
    //free(arr);
}
return 0;
}

