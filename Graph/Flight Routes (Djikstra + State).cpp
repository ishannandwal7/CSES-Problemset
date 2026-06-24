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
  int n,m,k;cin>>n>>m>>k;
  vector<vector<pair<int,int>>>adj(n+1);
  for(int i=0;i<m;++i){
    int a,b,c;cin>>a>>b>>c;
    adj[a].push_back({b,c});
  }
  vector<priority_queue<ll>>dis(n+1);
  dis[1].push(0);
  priority_queue<vector<ll>,vector<vector<ll>>,greater<vector<ll>>>pq;
  pq.push({0,1});
  while(!pq.empty()){
    auto head = pq.top();
    pq.pop();
    ll D = head[0],node =head[1];
    ll maxD = dis[node].top();
    if(D>maxD && dis[node].size()==k){continue;}
    for(auto child:adj[node]){
      ll newD = D+child.second;
      if(dis[child.first].size()<k){
        dis[child.first].push(newD);
        pq.push({newD,child.first});
      }else{
        if(newD < dis[child.first].top()){
          dis[child.first].push(newD);
          dis[child.first].pop();
          pq.push({newD,child.first});
        }
      }
    }
  }
  vector<ll>ans;
  while(!dis[n].empty()){
    ans.push_back(dis[n].top());
    dis[n].pop();
  }
  reverse(begin(ans),end(ans));
  for(auto x:ans){
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