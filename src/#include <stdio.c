#include <stdio.h>
void main(){
    int x,y,z,investment,total;
    //x=additional; y=initial amt; z=goal
    y=0;
    total=0;
    scanf("%d", &z);
    while(z>=total){
        investment+=x;
        y+=x;
        total=2*(y+x);
        y=total;
    }
}