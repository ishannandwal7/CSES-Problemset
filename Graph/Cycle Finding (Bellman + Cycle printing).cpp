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

void solve() {
  int n,m;cin>>n>>m;
  vector<vector<int>>edges(m);
  for(int i=0;i<m;++i){
    int a,b,c;cin>>a>>b>>c;
    edges[i] = {a,b,c};
  }

  // Need to keep dis = 0 for every node,since only need to find the -ve cycle , and source is not given
  vector<ll>dis(n+1,0);
  vector<int>parent(n+1,-1);
  int lastNode = -1;
  for(int i=0;i<n;++i){
    lastNode = -1;
    for(auto x:edges){
      ll u=x[0],v=x[1],d=x[2];
      if(dis[u]+d<dis[v]){
        dis[v] = dis[u] + d;
        parent[v] = u;
        lastNode = v;
      }
    }
  }
  if(lastNode == -1){
    cout<<"NO\n";
    return ;
  }
  vector<int>cycle;
  
  //there can be two types of last node 
  // type 1 : which is the part of cycle 
  // type 2 : which is not the part of cycle

  // simply go back N times to find the node which is part of cycle 
  // why N ? because in worst case there would single chain graph like a->b->c->d , 
  // going back N times help to find the node which is in cycle
  for(int i=0;i<n;++i){
    lastNode = parent[lastNode];
  }

  // Reconstruct the -ve cycle with help of parent array 
  int curr = lastNode;
  do {
    cycle.push_back(curr);
    curr = parent[curr];
  }while(curr != lastNode);

  cycle.push_back(curr);
  reverse(begin(cycle),end(cycle));
  cout<<"YES\n";
  for(auto x:cycle){
    cout<<x<<" ";
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