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
  int components,maxSize;
  DSU(int n){
    size.resize(n,1);
    parent.resize(n);
    iota(begin(parent),end(parent),0);
    components = n;
    maxSize = 1;
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
    maxSize = max({maxSize,size[V],size[U]});
    return 1;
  }
};


// dfs to get topo sort
void dfs(int node,vector<vector<int>>&adj,vector<bool>&vis,stack<int>&st){
  if(vis[node]){return ;}
  vis[node]=1;
  for(auto x:adj[node]){
    if(!vis[x]){
      dfs(x,adj,vis,st);
    }
  }
  st.push(node);
  return;
}

void dfs1(int node,vector<vector<int>>&adj,vector<bool>&vis,vector<int>&scc,int cmpId){
  vis[node]=1;
  scc[node] = cmpId;
  for(auto x:adj[node]){
    if(!vis[x]){
      dfs1(x,adj,vis,scc,cmpId);
    }
  }
  return ;
}

vector<long>dp;
long f(int node,vector<vector<int>>&adj,unordered_map<int,long>&sccSum){
  if(dp[node]!=-1){return dp[node];}
  long ans = 0;
  for(auto x:adj[node]){
    ans = max(ans,f(x,adj,sccSum));
  }
  return dp[node] = ans+sccSum[node];
}



void solve(){
  int n,m;cin>>n>>m;
  vector<vector<int>>adj(n+1),rev(n+1);
  vector<vector<int>>edges;
  vector<int>arr(n+1);
  vector<bool>vis(n+1,0);
  vector<int>scc(n+1,-1);
  stack<int>st;
  for(int i=1;i<=n;++i){cin>>arr[i];}
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    edges.push_back({a,b});
    adj[a].push_back(b);
    rev[b].push_back(a);
  }
  for(int i=1;i<=n;++i){
    if(!vis[i]){
      dfs(i,adj,vis,st);
    }
  }
  vis.clear();
  vis.resize(n+1,0);
  int cmpId = 0;
  while(!st.empty()){
    int head = st.top();st.pop();
    if(!vis[head]){
      dfs1(head,rev,vis,scc,cmpId);
      ++cmpId;
    }
  }
  unordered_map<int,long>sccSum;
  for(int i=1;i<=n;++i){
    sccSum[scc[i]]+=arr[i];
  }

  vector<vector<int>>condensedGraph(cmpId);
  for(auto x:edges){
    int node1 = x[0],node2 = x[1];
    int sccCmp1 = scc[node1],sccCmp2= scc[node2];
    if(sccCmp1 == sccCmp2){continue;}
    condensedGraph[sccCmp1].push_back(sccCmp2);
  }

  long ans = 0;
  dp.resize(cmpId,-1);
  for(int i=0;i<cmpId;++i){
    ans = max(ans,f(i,condensedGraph,sccSum));
  }
  cout<<ans<<"\n";


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