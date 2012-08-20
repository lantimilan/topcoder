// =========================================================
// 
//       Filename:  electric_grid.cpp
// 
//    Description:  codesprint genesys
// 
//        Version:  1.0
//        Created:  06/30/2012 11:56:36 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/30/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef long long int64;
typedef pair<int,int> pii;

int size[2005];
int comp[2005];
int edge[2005][2005];
vector<pair<int, pii> > elist;

int getcomp(int d)
{
    while(comp[d]!=d) d=comp[d];
    return d;
}

// kruskal's MST
void solve()
{
    int N, M, K;
    scanf("%d%d%d", &N, &M, &K);
    memset(edge, -1, sizeof edge);
    for(int i=0; i<M; ++i) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a; --b;
        edge[a][b]=edge[b][a]=c;
        elist.push_back(make_pair(c, pii(a,b)));
    }

    sort(elist.begin(), elist.end());
    for(int i=0; i<N; ++i) { comp[i]=i; size[i]=1; }

    int ncomp=N;
    int64 ans=0;
    for(int i=0; i<int(elist.size()); ++i) {
        if (ncomp<=K) break;
        int a, b, c;
        a=elist[i].second.first; b=elist[i].second.second;
        c=elist[i].first;
        int pa, pb;
        pa=getcomp(a); pb=getcomp(b);
        if (pa==pb) continue;
        if (size[pa]>=size[pb]) {
            comp[pb] = pa;
            size[pa] += size[pb];
        }
        else {
            comp[pa] = pb;
            size[pb] += size[pa];
        }
        ans += c;
        ncomp--;
    }
    if (ncomp>K) puts("Impossible!");
    else printf("%lld\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}
