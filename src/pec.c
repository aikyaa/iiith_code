#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int a[N],b[N],c[N],d[N];
    int area=0;
    for (i=0;i<N;i++){
        scanf("%d %d %d %d", &[i], &b[i], &c[i], &d[i]);
        area+=((b[i]-a[i])*(d[i]-c[i]));
    }
    //what if the rectangles overlap?
}