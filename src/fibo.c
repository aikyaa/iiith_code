#include <stdio.h>
int main(){
    int n,x,y,S;
    scanf("%d %d %d", &n,&x,&y);
if (n>1){
    printf("%d %d ", x,y);
    for (int i=0;i<= (n-3);i++){
        S=x+y;
        printf("%d ", S);
        x=y;
        y=S;
    }
}
else {
    printf("%d", x);
}
    return 0;
}