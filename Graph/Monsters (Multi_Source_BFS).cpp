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

void print2DPath(vector<vector<int>>&parent,int i,int j){
  unordered_map<int,char>mp;
  mp[0]='L';
  mp[1]='R';
  mp[2]='U';
  mp[3]='D';
  vector<char>path;
  while(parent[i][j]!=-1){
    int val = parent[i][j];
    path.push_back(mp[val]);
    i-=dx[val];
    j-=dy[val];
  }
  reverse(begin(path),end(path));
  for(auto x:path){
    cout<<x;
  }
  return ;
}

void solve() {
  int n,m;cin>>n>>m;
  vector<vector<char>>grid(n,vector<char>(m,' '));
  vector<vector<int>>dis(n,vector<int>(m,1e9));
  vector<vector<int>>parent(n,vector<int>(m,-1));
  queue<pair<int,int>>q;
  int startX = -1,startY = -1;
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      char ch;cin>>ch;
      grid[i][j]= ch;
      if(ch=='M'){q.push({i,j});dis[i][j]=0;}
      if(ch=='A'){startX = i,startY = j;}
    }
  }

  while(!q.empty()){
    int sz = q.size();
    while(sz--){
      auto [i,j] = q.front();q.pop();
      for(int it=0;it<4;++it){
        int X = i+dx[it];
        int Y = j+dy[it];
        if(X>=0 && X<n && Y>=0 && Y<m && grid[X][Y]!='#' && dis[i][j]+1<dis[X][Y]){
            q.push({X,Y});
            dis[X][Y] = dis[i][j]+1;
        }
      }
    }
  }
  queue<vector<int>>qu;
  vector<vector<bool>>vis(n,vector<bool>(m,0));
  qu.push({0,startX,startY});
  vis[startX][startY] = 1;
  while(!qu.empty()){
    auto head = qu.front();qu.pop();
    int i = head[1],j=head[2],D=head[0];
    if(i==n-1 || i==0 || j==0 || j==m-1){cout<<"YES\n"<<D<<"\n";print2DPath(parent,i,j);return ;}
    for(int it=0;it<4;++it){
      int X = i+dx[it];
      int Y = j+dy[it];
      if(X>=0 && X<n && Y>=0 && Y<m && grid[X][Y]=='.' && D+1<dis[X][Y] && !vis[X][Y]){
        qu.push({D+1,X,Y});
        parent[X][Y] = it;
        vis[X][Y] = 1;
      }
    }
  }
  cout<<"NO\n";
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