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

void solve(){
  long n,k,x,a,b,c;
  cin>>n>>k>>x>>a>>b>>c;
  vector<long>arr;
  arr.push_back(x);
  for(ll i=1;i<n;++i){
    arr.push_back(getNum(arr[i-1],a,b,c));
  }

  ll i=0,j=0;
  long sum=0;
  while(j<k && j<n){sum+=arr[j++];}

  ll xorr = sum;
  while(j<n){
    sum+=arr[j++];
    sum-=arr[i++];
    xorr ^= sum;
  }
 
  cout<<xorr<<" "<<"\n";

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