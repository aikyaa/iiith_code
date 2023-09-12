#include <stdio.h>
void main(){
    int N,D;
    scanf("%d", &N);
    int grid[N+2][N+2];
    for(int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            scanf(" %d", &grid[i][j]);
        }
        scanf("\n");
    }
    int temp1=grid[1][1];
    int temp2=grid[1][N];
    int temp3=grid[N][1];
    int temp4=grid[N][N];
    scanf("%d", &D);
    if (D=0){
        for (int k=1;k<=N;k++){
            grid[1][k-1]=grid[1][k];
        }
        for (int m=N;m>=1;m--){
            grid[m+1][1]=grid[m][1];
        }
        for (int l=N;l>=1;l--){
            grid[N][l+1]=grid[N][l];
        }
        for (int n=1;n<=N;n++){
            grid[N][n-1]=grid[N][n];
        }
        grid[2][1]= temp1;
        grid[N][2]= temp3;
        grid[1][N-1]= temp2;
        grid[N-1][N]= temp4;
    } else {
        for (int l=N;l>=1;l--){
            grid[1][l+1]=grid[1][l];
        }
        for (int m=N;m>=1;m--){
            grid[m+1][N]=grid[m][N];
        }
        for (int k=1;k<=N;k++){
            grid[N][k-1]=grid[N][k];
        }
        for (int n=1;n<=N;n++){
            grid[n-1][1]=grid[n][1];
        }
        grid[1][2]= temp1;
        grid[2][N]= temp2;
        grid[N-1][1]= temp2;
        grid[N][N-1]= temp4;
    }
    for(int i=1; i<=N; i++){
        for (int j=1; j<=N; j++){
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }    
}