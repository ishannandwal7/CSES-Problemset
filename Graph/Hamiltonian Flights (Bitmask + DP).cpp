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
const int mod = 1e9 + 7;
const int MX = 20;
 
int dx[8] = {0,0,-1,-1,-1,1,1,1};
int dy[8] = {-1,1,-1,0,1,-1,0,1};
 
//         L, R, U, D
// int dx[4] ={0,0,-1,1};
// int dy[4] ={-1,1,0,0};


vector<vector<ll>>dp;
ll f(int node,int mask,vector<vector<int>>&adj,int &n){
  if(node == n-1){
    return mask == ((1<<n)-1);
  }
  if(dp[node][mask]!=-1){return dp[node][mask];}
  ll ans = 0;
  for(auto x:adj[node]){
    if(!(mask & (1<<x))){
      ans = (ans + f(x,(mask | (1<<x)),adj,n))%mod;
    }
  }
  return dp[node][mask] = ans;
}

void solve(){
  int n,m;cin>>n>>m;
  vector<vector<int>>adj(n);
  for(int i=0;i<m;++i){
    int a,b;cin>>a>>b;
    --a;--b;
    adj[a].push_back(b);
  }
  dp.resize(n,vector<ll>((1<<n),-1));
  cout<<f(0,1,adj,n);
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