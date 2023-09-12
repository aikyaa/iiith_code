#include <stdio.h>
void main(){
    int N;
    scanf("%d", &N);
    int var=0;
    int a[N],b[N],c[N],d[N];
    int area=0;
    for (int i=0;i<N;i++){
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
        area+=((b[i]-a[i])*(d[i]-c[i]));
    }
    int commonx[N],commony[N];
    int excess=0;
    int x=0;
    int y=0;
    for (int j=0; j<N; j++){
        for(int p=0; p<N; p++){
        for(int k=a[j]; k<=b[j]; k++){
            for(int l=a[j+p]; l<=b[j+p]; l++){
                if (k==l){
                    commonx[x]=k;
                    x+=1;
                }
        }
        }
        for(int n=a[j]; n<=b[j]; n++){
            for(int o=a[j+p]; o<=b[j+p]; o++){
                if (n==o){
                    commony[y]=n;
                    y+=1;
                }
        }
        }
        excess+=(x*y);
        for(int q=0; q<=x; q++){
            for(int r=0; r<N; r++){
                if (arr[r]==q);
                var+=1;
            }
        }
        y=0;
        x=0;
    }
    }
    if (var%N==0)
    printf("%d", area-excess);
}