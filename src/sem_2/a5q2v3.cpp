#include<bits/stdc++.h>
using namespace std;

void bfs(int root, vector<long long int> &d, vector<bool> &vis, vector<vector<pair<int, long long int>>> &adj){
    queue<int> Q;
    Q.push(root);
    d[root]=0;
    vis[root]=true;
    while(!Q.empty()){
        int curr=Q.front();
        Q.pop();
        for(int i=0; i<adj[curr].size(); i++){
            int neighbor=adj[curr][i].first;
            if(!vis[neighbor]){
                Q.push(neighbor);
                vis[neighbor]=true;
                int temp=d[curr]+adj[curr][i].second;
                if (d[neighbor]==-1 || temp<d[neighbor]) d[neighbor]=temp;
            }
        }
    }
}

int main(){
    int offices, normals, fibers;
    cin>>offices>>normals>>fibers;
    vector<vector<pair<int,long long int>>> edges(offices);
    vector<long long int> min_latencies(offices, -1);
    vector<long long int> fiber_latencies(offices, -1);
    vector<bool> vis(offices, false);
    long long int adj[offices][offices]={0};
    int ans=0;
    for(int i=0; i<normals; i++){
        int x,y;
        long long int latency;
        cin>>x>>y>>latency;
        x--;
        y--;
        edges[x].push_back({y,latency});
        edges[y].push_back({x,latency});
    }
    for(int i=0; i<fibers; i++){
        int c;
        long long int latency;
        cin>>c>>latency;
        c--;
        edges[0].push_back({c,latency});
        edges[c].push_back({0,latency});
        if (fiber_latencies[c]==-1)fiber_latencies[c]=latency;
        else if(fiber_latencies[c]!=-1 && latency<fiber_latencies[c]){
            fiber_latencies[c]=latency;
            ans++;
        }
    }
    bfs(0, min_latencies, vis, edges);
    vector<bool> fiberchecked(offices, false);
    for(int i=0; i<edges[0].size(); i++){
        int end=edges[0][i].first;
        if(!fiberchecked[end] && fiber_latencies[end]!=-1 && min_latencies[end]!=-1 && min_latencies[end]<fiber_latencies[end]){
            ans++;
        }
        fiberchecked[end]=true;
    }
    cout<<ans;
    return 0;
}