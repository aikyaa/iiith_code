#include <stdio.h>
void main(){
    int z;
    int investment=1;
    scanf("%d", &z);
    if(z==0){
        printf("0");
    } else {
    while(z>2) {
    if (z%2 !=0){
        z=(z-1)/2;
        investment+=1;
    } else{
        z=z/2;
    }
    }
    printf("%d", investment);
    }
}