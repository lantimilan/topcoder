// =========================================================
// 
//       Filename:  D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2011 08:35:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2011, LI YAN
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
#include <queue>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef pair<int,LL> PIL;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define sz(x) int(x.size())

LL Gedge[1005][1005], Gcost[1005][1005]; 
LL edist[1005];

template<class T>
void checkmin(T &a, T b)
{ a = a<=b?a:b; }

class cmp {
public:
    bool operator()(int a, int b) { 
        if (edist[a]<0 && edist[b]<0) return a>b; 
        if (edist[a]<0 && edist[b]>=0) return true; 
        if (edist[a]>=0 && edist[b] < 0) return false;
        return edist[a]>edist[b];
    }
};

void solve()
{
    // all pair shortest path for Gedge
    // construct Gcost, if dist<=t_i, then c(u,v)=c_i
    //
    int n,m; cin >> n >> m;
    int x,y; cin >> x >> y; x--; y--;
    memset(Gedge,-1,sizeof Gedge); memset(Gcost,-1,sizeof Gcost);

    vector<vector<PIL> > adj(n);

    for(int i=0; i<n; ++i) Gedge[i][i]=0;
    for(int i=0; i<m; ++i) {
        int u,v; cin >> u >> v; u--; v--;
        LL w; cin >> w;
        if (Gedge[u][v] < 0 || Gedge[u][v] > w) Gedge[u][v]=Gedge[v][u]=w;

        bool found=false;
        for(int b=0; b<sz(adj[u]); ++b) if (adj[u][b].first == v) 
        { checkmin(adj[u][b].second, w); found = true; }
        if (!found) adj[u].PB(make_pair(v,w));
        found=false;
        for(int b=0; b<sz(adj[v]); ++b) if (adj[v][b].first == u) 
        { checkmin(adj[v][b].second, w); found = true; }
        if (!found) adj[v].PB(make_pair(u,w));
    }
    /*** floyd-warshall too slow?
    for(int k=0; k<n; ++k) for(int u=0; u<n; ++u) for(int v=u+1; v<n; ++v) 
    if (Gedge[u][k]>=0 && Gedge[k][v]>=0)
    {
        LL d = Gedge[u][k] + Gedge[k][v];
        if (Gedge[u][v]<0 || Gedge[u][v]>d) Gedge[v][u]=Gedge[u][v]=d;
    }****/

    for(int src=0; src<n; ++src)
    {
        memset(edist,-1,sizeof edist);
        int visit[1005] = {0};
        edist[src]=0;
        priority_queue<int,vector<int>,cmp> pq; pq.push(src);
        while(!pq.empty()) {
            int node = pq.top(); pq.pop(); if (visit[node]) continue;
            visit[node]=1;
            for(int b=0; b<sz(adj[node]); ++b) {
                int v = adj[node][b].first; if (visit[v]) continue;
                LL dd = edist[node] + adj[node][b].second;
                if (edist[v]<0 || edist[v] > dd) { edist[v] = dd; }
                pq.push(v);
            }
        }
        for(int dest=0; dest<n; ++dest) Gedge[src][dest]=edist[dest];
    }
    //for(int i=0; i<n; ++i) { for(int j=0; j<n; ++j) cout << Gedge[i][j] << " "; cout << endl; }

    LL t[1005], cost[1005]; memset(t,-1,sizeof t); memset(cost,-1,sizeof cost);
    for(int i=0; i<n; ++i) { cin >> t[i] >> cost[i]; }
    for(int u=0; u<n; ++u) for(int v=0; v<n; ++v) if (u!=v) {
        if (0<= Gedge[u][v] && Gedge[u][v] <= t[u]) Gcost[u][v] = cost[u];
    }

    // dijkstra, O(mn), could have been O(mlogn)
    int visit[1005]={0}; LL dist[1005]; memset(dist, -1, sizeof dist);
    dist[x]=0LL;
    while(!visit[y]) {
        LL kmin=-1;
        for(int k=0; k<n; ++k) if (!visit[k])
        { if (dist[k]>=0 && (kmin<0 || dist[k]<dist[kmin])) kmin=k; }
        if (kmin<0) break;
        visit[kmin]=1;
        for(int k=0; k<n; ++k) if (k!=kmin) {
            if (Gcost[kmin][k]>=0) {
                LL d = dist[kmin] + Gcost[kmin][k];
                if (dist[k]<0 || dist[k]>d) dist[k]=d;
            }
        }
    }
    LL ans = dist[y];
    cout << ans << endl;
}

int main()
{
    solve();
}
