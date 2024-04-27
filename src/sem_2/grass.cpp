#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<vector<int>> graph(n);
    for(int i=0; i<n-1; i++){
        int u,v;
        cin >> u >> v;
        u--;
        v--;

        graph[u].push_back(v);
        graph[v].push_back(u);

    }
    int ans=1;
    for(int i=0; i<n; i++){
        ans=max(ans, (int)graph[i].size());
    }
    cout << ans + 1;
    return 0;
}
///milk factory usaco
// vector<bool> vis(n, false);
// void dfs(int curr, vector<bool> &vis, vector<vector<int>> &adj)
//     if(vis[curr]) return;
//     vis[curr]=true;
//     for(auto nxt)
