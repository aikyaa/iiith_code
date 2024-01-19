#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int var=0;
    int a[N],b[N],c[N],d[N];
    int area=0;
    for (int i=0;i<N;i++){
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
    }
    for (int x=0; x<=100; x++){
        for(int y=0;y<=100;y++){
            for(int j=0; j<N; j++){
                if (a[j]<=x && b[j]>=x+1 && c[j]<=y && d[j]>=y+1){
                    area+=1;
                    break;
                }
            }
        }
    }
    printf("%d", area);
}
