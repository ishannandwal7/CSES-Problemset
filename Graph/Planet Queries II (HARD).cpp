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
const int MX = 20;
 
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

int dfs(int node,vector<int>&child,vector<bool>&vis,vector<int>&dis){
  if(vis[node]){return dis[node];}
  vis[node]=1;
  int childNode = child[node];
  return dis[node] = dfs(childNode,child,vis,dis)+1;
}

int lifting(int node,int jump,vector<vector<int>>&up){
  if(jump<0){return node;}
  for(int i=MX-1;i>=0;--i){
    if(jump & (1<<i)){
      node = up[node][i];
    }
  }
  return node;
}

void solve(){ 
  int n,q;cin>>n>>q;
  vector<int>child(n+1);
  for(int i=1;i<=n;++i){
    cin>>child[i];
  }
  vector<int>dis(n+1,0);
  vector<bool>vis(n+1,0);
  for(int i=1;i<=n;++i){
    if(!vis[i]){
      dfs(i,child,vis,dis);
    }
  }

  vector<vector<int>>up(n+1,vector<int>(MX,-1));
  for(int i=1;i<=n;++i){
    up[i][0]=child[i];
  }
  for(int jump = 1;jump<MX;++jump){
    for(int node = 1;node<=n;++node){
      up[node][jump] = up[up[node][jump-1]][jump-1];
    }
  }

  while(q--){
    int a,b;cin>>a>>b;
    int cycleStartNode = lifting(a,dis[a],up);
    if(lifting(a,dis[a]-dis[b],up)==b){
      cout<<dis[a]-dis[b]<<"\n";
    } else{
      if(lifting(cycleStartNode,dis[cycleStartNode]-dis[b],up)==b){
        cout<<(dis[cycleStartNode]-dis[b])+dis[a]<<"\n";
      }else{
        cout<<"-1\n";
      }
    }
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