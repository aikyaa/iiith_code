#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int a[N],b[N],c[N],d[N];
    int area=0;
    int countx[100];
    int county[100];
    for (int i=0;i<N;i++){
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
        area+=((b[i]-a[i])*(d[i]-c[i]));
    }
    for(int i=0; i<=100; i++){
        for(int j=0; j<N; j++){
            if (a[j]<=i && i<=b[j]){
                countx[j]+=1;
            }
             if (c[j]<=i && i<=d[j]){
                countx[j]+=1;
            }
        }
    }
    int sumx=0;
    int sumy=0;
    for (int k=0; k<=100; k++){
        if (countx[k]==2){
            sumx+=1;
        }
        if (county[k]>0){
            sumy+=1;
        }
    }
    area=sumx*sumy;
    printf("%d", area);
}