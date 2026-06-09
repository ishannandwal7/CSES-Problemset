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

int dx[4] ={0,0,-1,1};
int dy[4] ={-1,1,0,0};

void dfs(int i,int j,vector<vector<char>>&arr,int &n,int &m){
  arr[i][j]='#';
  for(int it=0;it<4;++it){
    int x = i+dx[it];
    int y = j+dy[it];
    if(x>=0 && x<n && y>=0 && y<m && arr[x][y]=='.'){
      dfs(x,y,arr,n,m);
    }
  }
  return ;
}
void solve() {
  int n,m;cin>>n>>m;
  vector<vector<char>>grid(n,vector<char>(m,'_'));
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      cin>>grid[i][j];
    }
  }
  int rooms =0 ;
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      if(grid[i][j]=='.'){
        ++rooms;
        dfs(i,j,grid,n,m);
      }
    }
  }
  cout<<rooms<<"\n";
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