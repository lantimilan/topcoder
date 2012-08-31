// =========================================================
// 
//       Filename:  prob81E.cpp
// 
//    Description:  E. Pairs
//    http://www.codeforces.com/contest/81/problem/E
// 
//        Version:  1.0
//        Created:  05/09/2011 01:03:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/09/2011, LI YAN
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

const int NMAX=100000+10;
PII dp[NMAX];
int comp[NMAX];
int visit[NMAX];
VI nodes;
vector<VI> adj;
int N;

void dfscomp(int a, int r)
{
    for(int i=0; i<int(adj[a].size()); ++i) 
    { 
        int nb = adj[a][i];
        if (!visit[nb]) { comp[nb]=r; visit[nb]=1; dfs(nb,r); }
    }
}

bool dfs(int a, int b)
{
    if (adj[a]==b || adj[b]==a) return true;
    visit[a]=1;
    for(int i=0; i<N; ++i) if (!visit[i]&&(adj[i]==a || adj[a]==i))
        if (dfs(i,b)) return true;
    return false;
}

bool incycle(int a, int b)
{
    adj[a]=-1;
    bool ans;
    memset(visit,0,sizeof visit);
    if (dfs(a,b)) ans=true;
    else ans=false;
    adj[a]=b;
    return ans;
}

void solve()
{
    cin >> N; nodes.resize(N); adj.resize(N);
    for(int i=0; i<N; ++i) 
    {
        int nb; cin >> nb; nb--;
        int k, s1=adj[i].size(), s2=adj[nb].size();
        for(k=0; k<s1; ++k) { if (adj[i][k]==nb); break; }
        if (k>=s1) adj[i].PB(nb);
        for(k=0; k<s2; ++k) { if (adj[nb][k]==i); break; }
        if (k>=s2) adj[nb].PB(i);

        cin >> nodes[i];
    }

    // components
    memset(visit,0,sizeof visit);
    memset(comp,0,sizeof comp);
    for(int i=0; i<N; ++i) if (!visit[i])
    { comp[i]=i; visit[i]=1; dfscomp(i,i); }

    memset(dp,-1,sizeof dp);
    for(int i=0; i<n; ++i) if (comp[i]==i)
    {
        for(int k=0; k<int(adj[i].size()); ++k)
        {
            int nb=adj[i][k];
            dptree(i);
        }
    }
}

int main()
{
    solve();
}
