// =========================================================
// 
//       Filename:  byteland.cpp
// 
//    Description:  interview street facebook challenge
// 
//        Version:  1.0
//        Created:  01/14/2012 04:01:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/14/2012, LI YAN
// 
// =========================================================
// 
// weighted min vertex cover bipartitite graph
// max flow
//
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

const int INF=1000000;

char v[100];
int c[100];
int cap[100][100];
int N, M;
int s, t;

void chmin(int &a, int b)
{
    if (a>b) a=b;
}

int augment()
{
    int visit[100]={0};
    int prev[100]; memset(prev, -1, sizeof prev);
    queue<int> que; que.push(s); visit[s]=1;
    while(!que.empty()) {
        int k = que.front(); que.pop();
        for(int i=0; i<N+2; ++i) if (!visit[i] && cap[k][i]) {
            que.push(i); visit[i]=1; prev[i]=k;
        }
    }
    if (prev[t]<0) return 0;
    int incr=INF;
    int k=t;
    while(prev[k]>=0) {
        int p=prev[k];
        chmin(incr, cap[p][k]);
        k=p;
    }
    assert(k==s);
    k=t;
    while(prev[k]>=0) {
        int p=prev[k];
        cap[p][k]-=incr; cap[k][p]+=incr;
        k=p;
    }
    assert(k==s);
    return incr;
}

int maxflow()
{
    int ans=0;
    int aug=0;
    while((aug=augment())) ans+=aug;
    return ans;
}

void solve()
{
    memset(cap, 0, sizeof cap);
    scanf("%d%d", &N, &M);
    s=N; t=N+1;
    for(int i=0; i<N; ++i) {
        char army[10];
        scanf("%s%d", army, &c[i]);
        v[i]=army[0];
    }
    for(int i=0; i<M; ++i) {
        int a, b; scanf("%d%d", &a, &b); --a, --b;
        if (v[a]!=v[b]) { 
            cap[a][b]=cap[b][a]=INF; //printf("a %d b %d\n", a, b);
        }
    }
    for(int i=0; i<N; ++i) {
        if (v[i]=='A') cap[s][i]=c[i];
        else cap[i][t]=c[i];
    }

    //for(int i=0; i<N; ++i) if (cap[s][i]) printf("sss i %d cap %d\n", i, cap[s][i]);
    //for(int i=0; i<N; ++i) if (cap[i][t]) printf("ttt i %d cap %d\n", i, cap[i][t]);

    int ans=maxflow();
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t) solve();
}
