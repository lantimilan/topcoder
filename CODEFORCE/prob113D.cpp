// =========================================================
// 
//       Filename:  prob113D.cpp
// 
//    Description:  http://codeforces.com/contest/113/problem/D
// 
//        Version:  1.0
//        Created:  09/09/2011 01:06:07 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/09/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define sz(a) int(a.size())
#define EPS 1.0e-9

vector<vector<int> > graph;
vector<double> prob;
vector<double> dp[25][25];
int N;

vector<double> solve(int a, int b, double pp)
{
    if (!dp[a][b].empty()) return dp[a][b];

    int n=N;
    vector<double> ans(n,0.0);
    if (pp<EPS) { for(int i=0; i<n; ++i) ans[i]=1.0/n; return ans; }
    if (a==b) { ans[a]=1.0; return ans; }

    vector<double> tmp(n);
    // both move
    fill(tmp.begin(), tmp.end(), 0.0);
    double newpp = (1.0-prob[a])/sz(graph[a])*(1.0-prob[b])/sz(graph[b]);
    for(int i=0; i<sz(graph[a]); ++i)
    for(int j=0; j<sz(graph[b]); ++j)
    {
        int anext=graph[a][i], bnext=graph[b][j];
        vector<double> vec = solve(anext,bnext,newpp*pp);
        for(int i=0; i<n; ++i) tmp[i]+=vec[i];
    }
    for(int i=0; i<n; ++i) tmp[i]*=newpp;
    for(int i=0; i<n; ++i) ans[i]+=tmp[i];

    // both stay
    fill(tmp.begin(), tmp.end(), 0.0);
    newpp=prob[a]*prob[b];
    tmp=solve(a,b,newpp*pp);
    for(int i=0; i<n; ++i) tmp[i]*=newpp;
    for(int i=0; i<n; ++i) ans[i]+=tmp[i];

    // a stay, b move
    fill(tmp.begin(), tmp.end(), 0.0);
    newpp=prob[a]*(1.0-prob[b])/sz(graph[b]);
    for(int j=0; j<sz(graph[b]); ++j)
    {
        int anext=a, bnext=graph[b][j];
        vector<double> vec=solve(anext,bnext,newpp*pp);
        for(int i=0; i<n; ++i) tmp[i]+=vec[i];
    }
    for(int i=0; i<n; ++i) tmp[i]*=newpp;
    for(int i=0; i<n; ++i) ans[i]+=tmp[i];

    // a move, b stay
    fill(tmp.begin(), tmp.end(), 0.0);
    newpp=(1.0-prob[a])/sz(graph[a])*prob[b];
    for(int i=0; i<sz(graph[a]); ++i)
    {
        int anext=graph[a][i], bnext=b;
        vector<double> vec = solve(anext,bnext,newpp*pp);
        for(int i=0; i<n; ++i) tmp[i]+=vec[i];
    }
    for(int i=0; i<n; ++i) tmp[i]*=newpp;
    for(int i=0; i<n; ++i) ans[i]+=tmp[i];

    return dp[a][b]=ans;
}

int main()
{
    int n,m,a,b; cin >> n >> m >> a >> b;
    N=n;
    --a; --b;
    graph.resize(n); prob.resize(n);
    for(int i=0; i<m; ++i)
    {
        int p,q; cin >> p >> q;
        --p; --q;
        graph[p].push_back(q);
        graph[q].push_back(p);
    }
    for(int i=0; i<n; ++i) { cin >> prob[i]; }

    vector<double> ans = solve(a,b,1.0);
    for(int i=0; i<n; ++i)
    { if (i) cout << ' '; cout << ans[i]; }
    cout << endl;
}
