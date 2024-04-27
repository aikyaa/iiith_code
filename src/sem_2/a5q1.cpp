#include<bits/stdc++.h>
using namespace std;

void dfs(int root, vector<bool> &vis, vector<vector<int>> &adj){
    if (vis[root]) return;
    vis[root]=true;
    for(int neighbor: adj[root]){
        if(!vis[neighbor]) dfs(neighbor, vis, adj);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n);
    vector<bool> vis(n, false);
    vector<int> roots(1,0);
    for(int i=0; i<m; i++){
        int x,y;
        cin>>x>>y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for(int i=0; i<n; i++){
        if (!vis[i]){
            roots.push_back(i+1);
            dfs(i, vis, adj);
        }
    }
    cout<<roots.size()-2<<"\n";
    for(int i=1; i<((int)roots.size()-1); i++){
        cout<<roots[i]<<" "<<roots[i+1]<<"\n";
    }
    return 0;
}