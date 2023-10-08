#include <stdio.h>
int step(int minion_locations[][2], int x, int y, int max_minions, int max_y, int max_x, int fy){
    int count=0;
    //making sure we're not reaching a minion
    for(int o=0;o<max_minions;o++){
        if (minion_locations[o][0]==x+1&&minion_locations[o][1]==y+1){
            return 0;
        }
    }
    if (x==max_x-1 && y==fy){
        return 1;
    }
    if(x+1<max_x){
        if (y+2<max_y){
            count+=step(minion_locations,x+1,y+2,max_minions,max_y,max_x,fy);
        }
        if (y>=2){
            count+=step(minion_locations,x+1,y-2,max_minions,max_y,max_x,fy);
        }
    }
    if (x+2<max_x){
        if (y+1<max_y){
            count+=step(minion_locations,x+2,y+1,max_minions,max_y,max_x,fy);
        }
        if (y>=1){
            count+=step(minion_locations,x+2,y-1,max_minions,max_y,max_x,fy);
        }
    }
    return count;
}
int main(){
    int max_y,max_x,max_minions;
    scanf("%d %d %d", &max_x, &max_y, &max_minions);
    int minion_locations[max_minions][2];
    for(int a=0;a<max_minions;a++){
        scanf("%d %d", &minion_locations[a][0], &minion_locations[a][1]);
    }
    const long long int MOD=1e9+7;
    for(int fy=0;fy<max_y;fy++){
        int sum=0;
        for(int iy=0; iy<max_y; iy++){
            sum+=step(minion_locations,0,iy,max_minions,max_y,max_x,fy);
        }
        printf("%lld ",sum%MOD);
    }
    return 0;
}