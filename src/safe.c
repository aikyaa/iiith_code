#include <stdio.h>
int step(int coord[][2], int x, int y, int k, int m, int n){
    static int count=0;
    for(int i=0;i<k;i++){
        if (coord[i][0]==x&&coord[i][1]==y){
            return 0;
        }
    }
    if (x==n){
        count+=1;
    }
    if (x<=(m-1)&&y<=(n-2)){
        step(coord,x+1,y+2,k,m,n);
    }
    if (x<=(m-1)&&y<=(n+2)){
        step(coord,x+1,y-2,k,m,n);
    }
    if (x<=(m-2)&&y<=(n-1)){
        step(coord,x+2,y+1,k,m,n);
    }
    if (x<=(m-2)&&y<=(n+1)){
        step(coord,x+2,y-1,k,m,n);
    }
    return count;
}
int main(){
    int m,n,k;
    scanf("%d %d %d", &n, &m, &k);
    int coord[k][2];
    for(int a=0;a<k;a++){
        scanf("%d %d", &coord[a][0], &coord[a][1]);
    }
    int sum[m+1];
    for(int i=1;i<=m;i++){
        for(int j=0; j<n; j++){
            sum[i]+=step(coord,1,j,k,m,n);
        }
    }
    int max_index=1;
    const long long int MOD=1e9+7;
    for(int l=2;l<=m;l++){
        if(sum[max_index]<sum[l]){
            max_index=l;
        }
    }
    printf("%d %d", max_index, sum[max_index]%MOD);
    return 0;
}