// =========================================================
// 
//       Filename:  onepersongame.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/07/2012 11:04:53 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/07/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int M, N;
int grid[10][10];
int vis[10][10];

bool inbound(int a, int b)
{
    return 0<=a && a<M && 0<=b && b<N;
}

int calc(int a, int b, int cum)
{
    if (!inbound(a,b)) return cum;
    if (vis[a][b] || grid[a][b]==0) return cum;
    vis[a][b]=1;
    int d[][2]={ {-1,0}, {0,+1}, {+1,0}, {0,-1} };
    int ans=0;
    for(int x=0; x<4; ++x) {
        int i, j;
        i=a+d[x][0]; j=b+d[x][1];
        ans = max(ans, calc(i, j, cum+grid[a][b]));
    }
    vis[a][b]=0;
    return ans;
}

void solve()
{
    scanf("%d%d", &M, &N);
    for(int i=0; i<M; ++i) {
        for(int j=0; j<N; ++j)
            scanf("%d", &grid[i][j]);
    }
    int ans=0;
    for(int i=0; i<M; ++i)
    for(int j=0; j<N; ++j) if (grid[i][j]) {
        memset(vis, 0, sizeof vis);
        ans = max(ans, calc(i,j,0));
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}

// TLE
