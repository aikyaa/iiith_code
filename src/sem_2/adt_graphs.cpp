#include<bits/stdc++.h>
using namespace std;

int possible=0;

void dfs(int index,int target, vector<bool> &vis, vector<vector<int>> &adj){
    if (vis[index]) return;
    if (possible==1) return;
    if (index==target){
        possible=1;
        return;
    }  
    vis[index]=true;
    for(int i=0; i< (int)adj[index].size(); i++){
        if(!vis[adj[index][i]]) dfs(adj[index][i], target, vis, adj);
    }
}

void bfs(int root, vector<int> &d, vector<bool> &vis, vector<vector<int>> &adj){
    queue<int> Q;
    Q.push(root);
    d[root]=0;
    vis[root]=true;
    while(!Q.empty()){
        int curr=Q.front();
        Q.pop();
        for(int neighbor: adj[curr]){
            if(!vis[neighbor]){
                Q.push(neighbor);
                vis[neighbor]=true;
                d[neighbor]=d[curr]+1;
            }
        }
    }
}

int main(){
    int n; cin >> n;
    int k; cin>>k;
    vector<vector<int>> adj(n);
    vector<bool> vis(n, false);
    for(int i=0; i<k; i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int u, v;
    cin >> u>> v;
    dfs(u,v,vis,adj);
    cout<<possible;
    return 0;
}