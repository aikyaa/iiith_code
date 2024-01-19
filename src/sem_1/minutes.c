#include <stdio.h>
void main(){
    int h,m,s;
    scanf("%d:%d:%d", &h,&m,&s);
    float x=s/60.0;
    float min=h*60+m+x;
    printf("%f", min);
}