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

vector<int> printPath(vector<int>&parent,int &startNode,int &endNode){
  vector<int>arr;
  arr.push_back(startNode);
  while(endNode != startNode){
    arr.push_back(endNode);
    endNode = parent[endNode];
  }
  arr.push_back(startNode);
  return arr;
}

bool dfs(int node,int parent,vector<vector<int>>&adj,vector<bool>&vis,vector<int>&parentArr,int &startNode,int &endNode){
  vis[node]=1;
  for(auto x:adj[node]){
    if(x==parent){continue;}
    if(!vis[x]){
      parentArr[x] = node;
      if(dfs(x,node,adj,vis,parentArr,startNode,endNode)){return 1;}
    }else{
      startNode = x;
      endNode = node;
      return 1;
    }
  }
  return 0;
}
 
void solve() {
  int n,m;cin>>n>>m;
  vector<vector<int>>adj(n+1);
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  vector<int>parent(n+1);
  vector<bool>vis(n+1,0);
  iota(begin(parent),end(parent),0);
  for(int i=1;i<=n;++i){
    if(!vis[i]){
      int startNode = -1,endNode = -1;
      if(dfs(i,-1,adj,vis,parent,startNode,endNode)){
        auto path = printPath(parent,startNode,endNode);
        cout<<path.size()<<"\n";
        for(auto x:path){
          cout<<x<<" ";
        }
        return ;
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