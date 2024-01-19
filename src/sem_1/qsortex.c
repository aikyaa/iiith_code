#include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b){
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcasecmp(a,b);
}
int main(){
    char **arr=(char**)malloc(3*sizeof(char*));
    for(int j=0; j<3;j++){
        arr[j]=(char*)malloc(5*sizeof(char));
    }
    arr[0]="Test\0";
    arr[1]="sort\0";
    arr[2]="stri\0";
    // qsort(arr[],(size_t) 3,(size_t) sizeof(*arr),compare);
    for(int i=0; i<3; i++){
        qsort(arr[i],(size_t) 3,(size_t) 5*sizeof(char),compare);
        printf("%s\n", arr[i]);
    }
}