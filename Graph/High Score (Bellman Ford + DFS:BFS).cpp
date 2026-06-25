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

vector<bool> canReach(int n,vector<vector<int>>&edges){
  vector<vector<int>>adj(n);
  vector<bool>vis(n,0);
  for(auto x:edges){
    adj[x[1]].push_back(x[0]);
  }
  queue<int>q;
  q.push(n-1);
  vis[n-1]=1;
  while(!q.empty()){
    auto head = q.front();q.pop();
    for(auto x:adj[head]){
      if(!vis[x]){
        q.push(x);
        vis[x]=1;
      }
    }
  }
  return vis;
}

ll bellman_ford(int N,int src,vector<vector<int>>&edges,vector<bool>&vis){
  vector<ll>dis(N,LLONG_MIN);
  dis[src] =0;
  for(int i=0;i<N-1;++i){
    for(auto x:edges){
      if(dis[x[0]]!=LLONG_MIN && dis[x[0]]+x[2]>dis[x[1]]){
        dis[x[1]] = dis[x[0]]+x[2];
      }
    }
  }

   // Check for Cycle
  for(auto x:edges){
    if(dis[x[0]]!=LLONG_MIN && dis[x[0]]+x[2]>dis[x[1]]){
      if(vis[x[1]]){return -1;}
    }
  }
  return dis[N-1];
  
}



void solve() {
  int n,m;cin>>n>>m;
  vector<vector<int>>edges;
  for(int i=0;i<m;++i){
    int a,b,c;cin>>a>>b>>c;
    edges.push_back({a-1,b-1,c});
  }
  vector<bool>vis = canReach(n,edges);
  cout<<bellman_ford(n,0,edges,vis);
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