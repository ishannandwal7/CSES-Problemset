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

long getNum(long prev,long a,long b,ll c){
  return (a*prev+b)%c;
}

void dfs(int node,vector<vector<pair<int,int>>>&adj,vector<bool>&edges,vector<int>&ans){
  while(!adj[node].empty()){
    auto child = adj[node].back();
    adj[node].pop_back();
    int edgeInd = child.second,edgeNode = child.first;
    if(edges[edgeInd]==true){continue;}
    edges[edgeInd] = 1;
    dfs(edgeNode,adj,edges,ans);
  }
  ans.push_back(node);
  return ;
}
void solve(){
  int n,m;cin>>n>>m;
  vector<bool>edges(m,0);
  vector<int>ans;
  vector<vector<pair<int,int>>>adj(n+1);
  vector<int>deg(n+1,0);
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    adj[a].push_back({b,i});
    adj[b].push_back({a,i});
    deg[a]++;
    deg[b]++;
  }

  bool imp = 0;
  for(auto x:deg){
    if(x&1){imp = 1;break;}
  }
  dfs(1,adj,edges,ans);
  if(ans[0] != ans.back() || ans.size()!=m+1 || imp ){cout<<"IMPOSSIBLE\n";return ;}
  for(auto x:ans){cout<<x<<" ";}
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