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
  vector<vector<int>>adj(n+1);
  vector<int>dis(n+1,1e9);
  vector<int>parent(n+1,0);
  iota(begin(parent),end(parent),0);
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  dis[1]=0;
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
  pq.push({0,1});
  while(!pq.empty()){
    auto [D,node] = pq.top();pq.pop();
    if(D>dis[node]){continue;}
    for(auto x:adj[node]){
      if(D+1<dis[x]){
        dis[x] = D+1;
        pq.push({D+1,x});
        parent[x]=node;
      }
    }
  }
  if(dis[n]==1e9){cout<<"IMPOSSIBLE\n";return ;}
  cout<<dis[n]+1<<"\n";
  int node = n;
  vector<int>arr;
  while(parent[node]!=node){
    arr.push_back(node);
    node = parent[node];
  }
  arr.push_back(node);
  reverse(begin(arr),end(arr));
  for(auto x:arr){
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