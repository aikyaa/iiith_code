#include <stdio.h>
void main(){
    int x,y,z,investment,total;
    //x=additional; y=initial amt; z=goal
    y=0;
    total=0;
    investment=0;
    x=1;
    scanf("%d", &z);
    while(z>=total){
        x=y+x;
        investment+=x;
        total=2*(y+x);
        y=x;
    }
    printf("%d", investment);
}