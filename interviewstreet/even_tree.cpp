// =========================================================
// 
//       Filename:  even_tree.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/26/2012 10:12:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/26/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

int N, M;
int edge[105][105];
int vis[105];

int dfs(int s)
{
    if (vis[s]) return 0;
    vis[s]=1;
    int ans=1;
    for(int t=0; t<N; ++t) if (!vis[t] && edge[s][t])
        ans += dfs(t);

    return ans;
}

void solve()
{
    int ans=0;
    bool update=true;
    while(update) {
        update = false;
        int minsize = N;
        int s0, t0;
        int curr;
        s0 = t0 = -1;
        for(int s=0; s<N; ++s)
        for(int t=0; t<N; ++t)
        if (edge[s][t]) {
            edge[s][t] = edge[t][s] = 0;
            memset(vis, 0, sizeof vis);
            curr = min(dfs(s), dfs(t));
            if (curr%2==0 && curr < minsize) {
                minsize = curr; s0=s; t0=t;
            }
            edge[s][t] = edge[t][s] = 1;
        }
        if (s0 >= 0) {
            update=true; ans++;
            edge[s0][t0]=edge[t0][s0]=0;
        }
    }
    printf("%d\n", ans);
}

int main()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        edge[a][b] = edge[b][a] = 1;
    }
    solve();

}
