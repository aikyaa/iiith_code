#include <stdio.h>
#include <stdlib.h>
int step(int minion_locations[][2], int x, int y, int max_minions, int max_y, int max_x, int fy, int *store_counts){
    int count=0;
    if(x>=max_x || y>=max_y){
        return 0;
    }
    //reducing time
    if(store_counts[x*max_y+y]!=-1){
        return store_counts[x*max_y+y];
    }
    //making sure we're not reaching a minion,store_counts
    for(int o=0;o<max_minions;o++){
        if (minion_locations[o][0]==x+1&&minion_locations[o][1]==y+1){
            store_counts[x*max_y+y]=0;
            return 0;
        }
    }
    if (x==max_x-1 && y==fy){
        store_counts[x*max_y+y]=1;
        return 1;
    }
    if(abs(fy-y)/2>(max_x-x)){
        store_counts[x*max_y+y]=0;
        return 0;
    }
    if(x+1<max_x){
        if (y+2<max_y){
            count+=step(minion_locations,x+1,y+2,max_minions,max_y,max_x,fy,store_counts);
        }
        if (y>=2){
            count+=step(minion_locations,x+1,y-2,max_minions,max_y,max_x,fy,store_counts);
        }
    }
    if (x+2<max_x){
        if (y+1<max_y){
            count+=step(minion_locations,x+2,y+1,max_minions,max_y,max_x,fy,store_counts);
        }
        if (y>=1){
            count+=step(minion_locations,x+2,y-1,max_minions,max_y,max_x,fy,store_counts);
        }
    }
    store_counts[x*max_y+y]=count;
    return count;
}
int main(){
    int max_y,max_x,max_minions;
    scanf("%d %d %d", &max_x, &max_y, &max_minions);
    int *store_counts=malloc(sizeof(int)*max_x*max_y);
    int minion_locations[max_minions][2];
    for(int a=0;a<max_minions;a++){
        scanf("%d %d", &minion_locations[a][0], &minion_locations[a][1]);
    }
    const long long int MOD=1e9+7;
    for(int fy=0;fy<max_y;fy++){
        int sum=0;
        for(int m=0;m<max_x;m++){
                for(int n=0;n<max_y;n++){
                    store_counts[m*max_y+n]=-1;
                }
            }
        for(int iy=0; iy<max_y; iy++){
            sum+=step(minion_locations,0,iy,max_minions,max_y,max_x,fy,store_counts);
        }
        printf("%lld ",sum%MOD);
    }
    return 0;
}