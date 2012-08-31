// =========================================================
// 
//       Filename:  prob104C.cpp
// 
//    Description:  http://codeforces.com/contest/104/problem/C
// 
//        Version:  1.0
//        Created:  08/08/2011 11:41:03 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/08/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

int n, m; 
int graph[105][105];
int prev[105];
int start, end;

void dfs(int k)
{
//cout << "dfs " << k << endl;
    for(int u=0; u<n; ++u)
    {
        if (graph[k][u]) {
            if (prev[u]>=0) 
            { if (prev[k]!=u && start<0) { start=k; end=u; } }
            else { prev[u]=k; dfs(u); }
        }
    }
}

void solve()
{
    cin >> n >> m;
    string yes="FHTAGN!", no="NO";

    if (n!=m) { cout << no << endl; return; }

    for(int i=0; i<m; ++i)
    {
        int a,b; cin >> a >> b; --a; --b;
        graph[a][b]=graph[b][a]=1;
    }
    memset(prev,-1,sizeof prev); start=end=-1;
    // connected
    prev[0]=0; dfs(0);
    for(int i=0; i<n; ++i)
        if (prev[i]<0) { cout << no << endl; return; }
        //cout << (i+1) << ' ' << prev[i]+1 << endl;
    // cycle length >=3
    //assert(start>=0 && end>=0); cout << start << ' ' << end << endl;
    int len=1, node=start;
    while(node!=end) { node=prev[node]; ++len; }
    if (len>=3) cout << yes << endl;
    else cout << no << endl;
}

int main()
{
    solve();
}
