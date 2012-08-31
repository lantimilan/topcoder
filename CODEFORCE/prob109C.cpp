// =========================================================
// 
//       Filename:  prob109C.cpp
// 
//    Description:  http://codeforces.com/contest/109/problem/C
// 
//        Version:  1.0
//        Created:  09/09/2011 11:03:22 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/09/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <set>
#include <utility>
#include <vector>
using namespace std;

#define sz(a) int(a.size())

typedef long long LL;
typedef pair<int,int> pii;

int n;
vector<set<int> > graph;

set<pii> lucky;

bool islucky(int n)
{
    while(n) { 
        if (n%10!=4 && n%10!=7) return false;
        n/=10;
    }
    return true;
}

void dfs(int v, map<int,bool> &visit)
{
    visit[v]=true;
    for(int i=0; i<sz(graph[v]); ++i)
        if (!visit.count(graph[v][i]))
            dfs(graph[v][i]);
}

LL solve(int v, int k, int &n)
{
    if (k>=sz(lucky)) {
        n=0;
        if (v>=0)
        {
            map<int,bool> mp;
            dfs(v,mp);
            n=mp.size();
        }
        return 0LL;
    }
    pii edge=lucky[k];
    int n1, n2;
    LL s1, s2;
    s1 = solve(edge.first,k+1,n1);
    s2 = solve(edge.second,k+2,n2);
    n=n1+n2;
    return s1+s2+n1*(n1-1)*n2+n2*(n2-1)*n1;
}

int main()
{
    int n; scanf("%d",&n);   
    graph.resize(n);
    for(int i=0; i<n-1; ++i)
    {
        int u,v,w; scanf("%d%d%d",&u,&v,&w);
        --u; --v;
        graph[u].insert(v);
        graph[v].insert(u);
        if (isluck(w)) lucky.push_back(pii(u,v));
    }
    LL ans = solve(-1,0,n);
    cout << ans << endl;
}
