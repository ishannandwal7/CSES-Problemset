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
 
// int dx[8] = {0,0,-1,-1,-1,1,1,1};
// int dy[8] = {-1,1,-1,0,1,-1,0,1};
 
//         L, R, U, D
// int dx[4] ={0,0,-1,1};
// int dy[4] ={-1,1,0,0};

ll maximumFlow(){
    int n,m;cin>>n>>m;
    vector<vector<ll>>residualGraph(n+1,vector<ll>(n+1,0));
    vector<vector<int>>adj(n+1);
    for(int i=0;i<m;++i){
        int a,b,c;cin>>a>>b>>c;
        residualGraph[a][b]+=c;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll ans = 0;
    while(1){
        // do BFS to get shortest path 
        queue<int>q;
        vector<int>parent(n+1,-1);
        q.push(1);
        parent[1] = 1;
        while(!q.empty()){
            auto head = q.front();
            q.pop();
            if(head == n){break;}
            for(auto x:adj[head]){
                if(residualGraph[head][x]>0 && parent[x]==-1){
                    parent[x] = head;
                    q.push(x);
                }
            }
        }

        if(parent[n]==-1){break;}

        // find the minmal value in that shortest path 
        int node = n;ll mini = LLONG_MAX;
        while(parent[node]!=node){
            int parentNode = parent[node];
            mini = min(mini,residualGraph[parentNode][node]);
            node = parentNode;
        }

        if(mini == LLONG_MAX){break;}

        // flow the minimal value from src & update residual graph
        node = n;
        while(parent[node]!=node){
            int parentNode = parent[node];
            residualGraph[parentNode][node] -= mini;
            residualGraph[node][parentNode] += mini;
            node = parentNode;
        }
        ans += mini;
    }
    return ans;
}

void solve() {
    cout<<maximumFlow();
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