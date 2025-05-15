#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    int graph[n][n];
    for(int j=0; j<n; j++){
        for(int k=0; k<n; k++){
            graph[j][k]=0;
        }
    }
    
    for(int i=0; i<q; i++){
        char command[15];
        int x;
        scanf("%[^ ]%*c", command);
        scanf("%d", &x);
        //printf("%s", command);
        if(strcmp(command, "INSERT")==0){
            int y;
            scanf("%d", &y);
            graph[x][y]=1;
            graph[y][x]=1;
        } else if(strcmp(command, "DELETE")==0){
            int y;
            scanf("%d", &y);
            if (graph[x][y]==0) printf("-1\n");
            else{
                graph[x][y]=0;
                graph[y][x]=0;
            }
        } else if(strcmp(command, "NUM_NEIGHBORS")==0){
            printf("hi");
            int count=0;
            for(int l=0; l<n; l++){
                if(graph[x][l]==1) count++;
            }
            printf("%d\n", count);
        }
    }
    return 0;
}