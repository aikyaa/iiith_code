#include <stdio.h>
void main(){
    int N,temp1,temp2,temp3,temp4;
    scanf("%d", &N);
    int grid[N][N];
    for(int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            scanf(" %d", &grid[i][j]);
        }
        scanf("\n");
    }
    temp1=grid[0][0];
    temp2=grid[N-1][N-1];
    temp3=grid[0][N-1];
    temp4=grid[N-1][0];
    int D;
    scanf("%d", &D);
    if (D=0){
        for (int k=1;k<=N;k++){
            grid[0][k-1]=grid[0][k];
        }
        for (int l=N-1;l>=1;l--){
            grid[N-1][N-1]=grid[N-1][N-2];
        }
        for (int m=1;m<=n;m++){
            grid[0][k-1]=grid[0][k];
        }
    }
}