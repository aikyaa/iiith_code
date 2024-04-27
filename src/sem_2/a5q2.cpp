#include<bits/stdc++.h>
using namespace std;

void bfs(int root, vector<long long int> &d, vector<bool> &vis, vector<vector<pair<int, long long int>>> &adj, vector<long long int> &fiber_edge){
    queue<int> Q;
    Q.push(root);
    d[root]=0;
    vis[root]=true;
    while(!Q.empty()){
        int curr=Q.front();
        Q.pop();
        for(int i=0; i<adj[curr].size(); i++){
            int neighbor=adj[curr][i].first;
            int temp=d[curr]+adj[curr][i].second;
            if (d[neighbor]==-1 || temp<d[neighbor]) d[neighbor]=temp;
            if(curr==0){
                if (fiber_edge[neighbor]!=-1 && d[neighbor]>fiber_edge[neighbor]){
                    d[neighbor]=fiber_edge[neighbor];
                }
            }
            if(!vis[neighbor]){
                Q.push(neighbor);
                vis[neighbor]=true;
            }
        }
    }
}

int main(){
    int offices, normals, fibers;
    cin>>offices>>normals>>fibers;
    vector<vector<pair<int,long long int>>> edges(offices);
    vector<long long int> fiber_edges(offices, -1);
    vector<int> added_edges(offices, -1);
    vector<long long int> min_latencies(offices, -1);
    vector<bool> vis(offices, false);
    long long int adj[offices][offices]={0};
    for(int i=0; i<normals; i++){
        int x,y;
        long long int latency;
        cin>>x>>y>>latency;
        x--;
        y--;
        edges[x].push_back({y,latency});
        edges[y].push_back({x,latency});
        if (x==0) added_edges[y]=1;
        if (y==0) added_edges[x]=1;
    }
    for(int i=0; i<fibers; i++){
        int c;
        long long int latency;
        cin>>c>>latency;
        c--;
        // edges[0].push_back({c,latency});
        // edges[c].push_back({0,latency});
        //fiber_edges.push_back({c, latency});
        fiber_edges[c]=latency;
        if (added_edges[c]!=1){
            edges[0].push_back({c,latency});
            edges[c].push_back({0,latency});
        }
    }
    bfs(0, min_latencies, vis, edges, fiber_edges);
    int ans=0;
    for(int i=0; i<offices; i++){
        //int end=fiber_edges[i].first;
        cout<<min_latencies[i]<<" ";
        cout<<added_edges[i]<<" ";
        cout<<fiber_edges[i]<<"\n";
        if(min_latencies[i]!=-1 && min_latencies[i]<fiber_edges[i]){
            ans++;
        }
    }
    cout<<ans;
    return 0;
}