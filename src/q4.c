#include <stdio.h>
int safe(int coord[][2],int k, int x, int y){
    for(int i=0;i<k;i++){
        if (coord[i][0]==x&&coord[i][1]==y){
            return 0;
        }
    }
    return 1;
}
int step(int x, int y, int m, int n){
    if (x==n&&y<=m){
        count+=1;
    }
    if (x<=(m-1)&&y<=(n-2)&&safe(coordx+1,y+2)){
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