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

void printPath(vector<int>&parent,int node){
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
void solve() {
  int n,m;cin>>n>>m;
  vector<vector<int>>adj(n+1);
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  queue<int>q;
  vector<bool>vis(n+1,0);
  vector<int>parent(n+1);
  iota(begin(parent),end(parent),0);
  int level =0 ;
  q.push(1);
  vis[1]=1;
  while(!q.empty()){
    int sz = q.size();
    ++level;
    while(sz--){
      auto head = q.front();q.pop();
      if(head == n){cout<<level<<"\n";printPath(parent,n);return ;}
      for(auto x:adj[head]){
        if(!vis[x]){
          vis[x]=1;
          q.push(x);
          parent[x]=head;
        }
      }
    }
  }
  cout<<"IMPOSSIBLE\n";
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