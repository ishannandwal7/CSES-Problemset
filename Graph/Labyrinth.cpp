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



string caculatePath(int i,int j,vector<vector<int>>&parent){
  unordered_map<int,char>directions;
  directions[0]='L';
  directions[1]='R';
  directions[2]='U';
  directions[3]='D';
  string ans="";
  while(parent[i][j]!=-1){
    int val = parent[i][j];
    ans+=directions[val];
    i -= dx[val];
    j -= dy[val];
  }
  reverse(begin(ans),end(ans));
  return ans;
}


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

string solve() {
  int n,m;cin>>n>>m;
  vector<vector<char>>grid(n,vector<char>(m,'_'));
  vector<vector<int>>parent(n,vector<int>(m,-1));
  int startX,startY,endX,endY;
  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      cin>>grid[i][j];
      if(grid[i][j]=='A'){startX = i;startY = j;}
      if(grid[i][j]=='B'){endX = i;endY = j;grid[i][j]='.';}
    }
  }
  queue<pair<int,int>>q;
  q.push({startX,startY});


  
  while(!q.empty()){
    int sz = q.size();
    while(sz--){
      auto head = q.front();q.pop();
      int i=head.first,j=head.second;
      if(i==endX && j==endY){return caculatePath(endX,endY,parent);}
      grid[i][j]='#';
      for(int it=0;it<4;++it){
        int X = i+dx[it];
        int Y = j+dy[it];
        if(X>=0 && X<n && Y>=0 && Y<m && grid[X][Y]=='.'){
          q.push({X,Y});
          grid[X][Y]='#';
          parent[X][Y]=it;
        }
      }
    }
  }
  return "";
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
    string dir = solve();
    if(dir.size()==0){
      cout<<"NO\n";
    }else{
      cout<<"YES\n";
      cout<<dir.size()<<"\n";
      cout<<dir<<"\n";
    }
  }

  return 0;
}