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
  bool merge(int u,int v){
    int U = findParent(u);
    int V = findParent(v);
    if(U==V){return 0;}
    if(size[U]<size[V]){
      size[V]+=size[U];
      parent[U]=V;
    }else{
      size[U]+=size[V];
      parent[V]=U;
    }
    --components;
    return 1;
  }
};

void solve(){
  int n,m;cin>>n>>m;
  DSU dsu(n);
  vector<vector<int>>edges;
  for(int i=0;i<m;++i){
    int a,b,c;cin>>a>>b>>c;
    edges.push_back({c,a,b});
  }
  sort(begin(edges),end(edges));
  ll totalCost =0 ;
  for(auto x:edges){
    if(dsu.merge(x[1]-1,x[2]-1)){
      totalCost += x[0];
    }
  }
  if(dsu.components!=1){cout<<"IMPOSSIBLE\n";return ;}
  cout<<totalCost<<"\n";
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