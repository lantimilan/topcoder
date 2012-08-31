// =========================================================
// 
//       Filename:  prob118E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/07/2011 10:41:26 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/07/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define sz(a) int((a).size())
#define MAXN 100005
typedef vector<int> VI;

vector<VI> graph,forward, backward;
int parent[MAXN];
int visit[MAXN];
int done[MAXN];
int finish[MAXN];
int N;
int order;
int numcomp;
int comp[MAXN];

void dfs(int v)
{
    visit[v]=1;
    for(int i=0; i<sz(graph[v]); ++i)
    {
        int next=graph[v][i];
        if (next == parent[v] || done[next]) { } // edge used, do nothing
        else { forward[v].push_back(next); backward[next].push_back(v); }

        if (!visit[next]) { parent[next]=v; dfs(next); }
    }
    finish[--order]=v;
    done[v]=1;
}

void dfs_rev(int v, int curr)
{
    visit[v]=1; comp[v]=curr;
    for(int i=0; i<sz(backward[v]); ++i)
    {
        int next=backward[v][i];
        if (!visit[next]) dfs_rev(next,curr);
    }
}

int main()
{
    int n, m; scanf("%d%d",&n,&m); N=n;
    graph.resize(n); forward.resize(n); backward.resize(n);

    for(int i=0; i<m; ++i)
    {
        int a,b; scanf("%d%d",&a,&b);
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    memset(parent,-1,sizeof visit);
    memset(visit,0,sizeof visit);
    memset(done,0,sizeof done);
    order=N;
    for(int i=0; i<n; ++i) if (!visit[i]) dfs(i);

    numcomp=0;
    memset(visit,0,sizeof visit);
    for(int i=0; i<n; ++i) 
    {
        int v=finish[i];
        if (!visit[v]) { 
            numcomp++;
            dfs_rev(v,v);
        }
    }
    if (numcomp>1) {
        printf("0\n");
    }
    else {
        for(int i=0; i<n; ++i)
        for(int j=0; j<sz(forward[i]); ++j)
            printf("%d %d\n", (i+1), (forward[i][j]+1));
    }
}

// 748156   Oct 7, 2011 10:18:39 PM     lantimilan  E - Bertown roads   GNU C++
// Accepted     750 ms  19600 KB 
