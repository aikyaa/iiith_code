#include<bits/stdc++.h>
using namespace std;
int offices;

typedef long long int element;

element** edges;

void bfs(int root, vector<long long int> &d, vector<bool> &vis){
    queue<int> Q;
    Q.push(root);
    d[root]=0;
    vis[root]=true;
    while(!Q.empty()){
        int curr=Q.front();
        Q.pop();
        for(int neighbor=0; neighbor<offices; neighbor++){
            if(edges[0][neighbor]!=0){
                int temp=d[curr]+edges[curr][neighbor];
                if (d[neighbor]==-1 || temp<d[neighbor]) d[neighbor]=temp;
                if(!vis[neighbor]){
                    Q.push(neighbor);
                    vis[neighbor]=true;
                }
            }
        }
    }
}

int main(){
    int normals, fibers;
    cin>>offices>>normals>>fibers;
    edges=(element**)malloc(offices*sizeof(element*));
    for(int i=0; i<offices; i++){
        edges[i]=(element*)malloc(offices*sizeof(element));
    }
    vector<long long int> min_latencies(offices, -1);
    vector<bool> vis(offices, false);
    vector<int> fiber_count(offices, 0);
    vector<int> fiber_latencies(offices, -1);
    int ans=0;
    for(int i=0; i<normals; i++){
        int x,y;
        long long int latency;
        cin>>x>>y>>latency;
        x--;
        y--;
        if(edges[x][y]==0 || edges[x][y]>latency){
            edges[x][y]=latency;
            edges[y][x]=latency;
        }
    }
    for(int i=0; i<fibers; i++){
        int c;
        long long int latency;
        cin>>c>>latency;
        c--;
        if (fiber_count[c]==1) ans++;
        if(fiber_count[c]==0) fiber_latencies[c]=latency;
        fiber_count[c]=1;
        if(edges[0][c]==0 || edges[0][c]>latency){
            edges[0][c]=latency;
            edges[c][0]=latency;
            fiber_latencies[c]=latency;
        }
    }
    bfs(0, min_latencies, vis);
    for(int i=0; i<offices; i++){
        if(fiber_latencies[i]!=-1 && min_latencies[i]!=-1 && min_latencies[i]<fiber_latencies[i]){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}