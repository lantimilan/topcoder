// =========================================================
// 
//       Filename:  B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/30/2011 08:15:43 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/30/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define sz(x) int(x.size())

int cntbit(int n)
{
    int ans=0;
    while(n) { n&=n-1; ++ans; }
    return ans;
}
void solve()
{
    int graph[10][10]; memset(graph, 0, sizeof graph);
    int m; cin >> m;
    for(int i=0; i<m; ++i) { int a,b; cin >> a >> b; --a; --b; graph[a][b]=graph[b][a]=1; }

    for(int b=0; b<(1<<5); ++b) if(cntbit(b) == 3) 
    {
        int cc=0; int v[4]; 
        for(int k=0; k<5; ++k) if (b & 1<<k) v[cc++] = k;
        bool good = true;
        for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) if (i!=j)
        { int a=v[i], b=v[j]; if (!graph[a][b]) good=false; }
        if (good) { cout << "WIN\n"; return; }
        good = true;
        for(int i=0; i<3; ++i) for(int j=0; j<3; ++j) if (i!=j)
        { int a=v[i], b=v[j]; if (graph[a][b]) good=false; }
        if (good) { cout << "WIN\n"; return; }
    }
    cout << "FAIL\n";
}

int main()
{
    solve();
}
