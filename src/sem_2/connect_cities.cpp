#include <bits/stdc++.h>
using namespace std;
long long int ans=0;
int cities=0;
void bfs(int root, vector<bool> &vis, vector<vector<pair<int,int>>> &adj, vector<int> &parent, vector<vector<int>> &new_adj){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    Q.push({0,root});
    parent[root]=-1;
    while(!Q.empty()){
        auto curr_node=Q.top();
        Q.pop();
        int curr=curr_node.second;
        int wt=curr_node.first;
        if(vis[curr]) continue;
        vis[curr]=true;
        cities++;
        ans+=wt;
        for(int i=0; i<adj[curr].size(); i++){
            int neighbor=adj[curr][i].first;
            parent[neighbor]=curr;
            int edge_wt=adj[curr][i].second;
            if(!vis[neighbor]){
                Q.push({edge_wt,neighbor});
            }
        }
    }
}

int main(){
    int n; cin >> n;
    int k; cin>>k;
    vector<vector<pair<int,int>>> adj(n);
    vector<bool> vis(n, false);
    for(int i=0; i<k; i++){
        int x,y,w;
        cin>>x>>y>>w;
        x--;
        y--;
        adj[x].push_back({y,w});
        adj[y].push_back({x,w});
    }
    vector<vector<int>> new_adj(n);
    vector<int> parent(n,-1);
    bfs(0,vis,adj, parent, new_adj);
    int possible=1;
    dfs()
    cout<<ans;
    return 0;
}