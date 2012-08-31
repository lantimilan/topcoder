// =========================================================
// 
//       Filename:  prob69E.cpp
// 
//    Description:  80E - Beavermuncher-0xFF 
//                  77C - Beavermuncher-0xFF 
// 
//        Version:  1.0
//        Created:  04/19/2011 09:45:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/19/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

int visit[100000+10];
int parent[100000+10];

long long getmax(int s, int n, const vector<VI> &adj, int k[])
{
    //cout << "getmax " << s << " " << k[s] << endl;
    visit[s] = 1;
    vector<long long> subtree;
    for(int i=0; i<int(adj[s].size()); i++)
    {
        int node = adj[s][i];
        if (visit[node]) continue;
        else parent[node] = s;
        k[node]--;
        subtree.push_back(getmax(node, n, adj, k));
    }
    sort(subtree.begin(), subtree.end());
    long long ret = 0LL;
    int num = int(subtree.size());
    for(int i=num-1; k[s] && i>=0; --i, --k[s])
    {    ret += subtree[i]+2; } //cout << subtree[i] << endl; }
    long long sum=0;
    for(int i=0; i<int(adj[s].size()); ++i) 
        if (parent[adj[s][i]]==s) sum += k[adj[s][i]];
    ret = ret+2*min((long long)k[s],sum);
    k[s] = max(0LL,k[s]-sum);
    //cout << (s+1) << " " << k[s] << " " << ret << endl;
    return ret;
}
void solve()
{
    int n; cin >> n;
    int k[100000+10];
    memset(visit, 0, sizeof visit);
    for(int i=0; i<n; ++i) cin >> k[i];
    vector<VI> adj(n);
    int a,b;
    for(int i=0; i<n-1; ++i)
    {
        cin >> a >> b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    int s; cin >> s; s--; parent[s] = s;
    cout << getmax(s,n,adj,k) << endl;
}

int main()
{
    solve();
}
