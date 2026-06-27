#include "bits/stdc++.h"
#include <algorithm>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
#define ll long long
#define pb push_back
#define all(v) v.begin(), v.end()
#define sz(x) (int)(x).size()
// const int mod = 1e9 + 7;
 
// int dx[8] = {0,0,-1,-1,-1,1,1,1};
// int dy[8] = {-1,1,-1,0,1,-1,0,1};
 
//         L, R, U, D
int dx[4] ={0,0,-1,1};
int dy[4] ={-1,1,0,0};
 
class DSU {
  vector<int>size,parent;
  public:
  int components;
  DSU(int n){
    size.resize(n,1);
    parent.resize(n);
    iota(begin(parent),end(parent),0);
    components = n;
  }
  int findParent(int node){
    if(parent[node]==node){return node;}
    return parent[node] = findParent(parent[node]);
  }
  void merge(int u,int v){
    int U = findParent(u);
    int V = findParent(v);
    if(U==V){return ;}
    if(size[U]<size[V]){
      size[V]+=size[U];
      parent[U]=V;
    }else{
      size[U]+=size[V];
      parent[V]=U;
    }
    --components;
    return ;
  }
};
stack<int>st;
void dfs(int node,vector<vector<int>>&adj,vector<bool>&vis){
  vis[node]=1;
  for(auto x:adj[node]){
    if(!vis[x]){
      dfs(x,adj,vis);
    }
  }
  st.push(node);
  return ;
}

vector<int> getPath(int node,vector<int>&parent){
  vector<int>path;
  while(node!=parent[node]){
    path.push_back(node);
    node = parent[node];
  }
  path.push_back(node);
  reverse(begin(path),end(path));
  return path;
}

void solve(){
  int n,q;cin>>n>>q;
  vector<int>arr(n+1);
  int LOG = 30;
  vector<vector<int>>up(n+1,vector<int>(LOG,-1));
  
  // binary lifting
  for(int i=1;i<=n;++i){
    cin>>up[i][0];
  }
  for(int j=1;j<LOG;++j){
    for(int i=1;i<=n;++i){
      up[i][j] = up[up[i][j-1]][j-1];
    }
  }

  while(q--){
    int x,k;cin>>x>>k;
    for(int j=LOG-1;j>=0;--j){
      if(k & (1<<j)){
        x = up[x][j];
        if(x==-1){break;}
      }
    }
    cout<<x<<"\n";
  }
  return ;
}
 
 
int main() {
  fast_io;
#ifndef ONLINE_JUDGE
  if (fopen("input.txt", "r")) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  }
#endif
 
  int t = 1;
  // cin >> t;
 
  while (t--) {
    solve();
  }
 
  return 0;
}