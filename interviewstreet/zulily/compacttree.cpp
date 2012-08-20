// =========================================================
// 
//       Filename:  compacttree.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/16/2012 02:05:23 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

int N, D;
int adj[55][55];
int seenA[55], seenB[55];
int dpA[55], dpB[55];

int calcA(int r, int budget, int root)
{
    if (seenA[r]) return dpA[r];
    int ans=1;
    seenA[r]=1; root=0;
    for(int i=0; i<N; ++i) if (!seenA[i] && adj[r][i]) {
        int prev;
        int curr = calcA(i, budget, prev);
        if (curr + prev <= budget) {
            ans *= (curr+1); //cost += curr+prev;
        }
    }
    return dp[r]=ans;
}

int calcB(int r, int budget)
{
    if (seenB[r]) return dpB[r];
    seenB[r]=1;
    int ans=0;
    for(int i=0; i<N; ++i) if (!seen[i] && adj[r][i]) {
        int cost;
        ans += calcA(i, budget, cost) + calcB(i, budget);
    }
    return dpB[r]=ans;
}

void solve()
{
    scanf("%d%d", &N, &D);
    memset(adj, 0, sizeof adj);
    memset(seenA, 0, sizeof seenA);
    memset(seenB, 0, sizeof seenB);
    memset(dpA, 0, sizeof dpA);
    memset(dpB, 0, sizeof dpB);
    for(int i=0; i<N-1; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a][b]=adj[b][a]=1;
    }
    int ans = calcA(0, D, D) + calcB(0, D);
    printf("%d\n", ans+1);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}
