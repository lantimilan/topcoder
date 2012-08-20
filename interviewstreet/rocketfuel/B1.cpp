// =========================================================
// 
//       Filename:  B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/19/2012 12:58:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/19/2012, LI YAN
// 
// =========================================================

// simulate two balls
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int N, M, K;
int board[1605][1605];
int seen[10005][4];
int vis[1605][1605];
int vis1[1605][1605];
int vis2[1605][1605];
pii lights[10005];

int dir[][2]={{-1,-1}, {-1,+1}, {+1,+1}, {+1,-1}};

void dfs(int l, int start, int r, int c, int x)
{
    vis[r][c]=1;
    int r2, c2;
    r2 = r+dir[x][0];
    c2 = c+dir[x][1];
    // bounce
    if (0<=r2 && r2<N) {
        if (0<=c2 && c2<M) {}
        else {
            x=(x+1)%4;
            if (c2<0) c2=-c2;
            else c2=M-2;
        }
    }
    else {
        if (0<=c2 && c2<M) {
            x=(x+1)%4;
            if (r2<0) r2=-r2;
            else r2=N-2;
        }
        else {
            x=(x+2)%4;
            if (r2<0) r2=-r2; else r2=N-2;
            if (c2<0) c2=-c2; else c2=M-2;
        }
    }
    if (!vis[r2][c2]) dfs(l,start,r2,c2,x);
}

int main()
{
    scanf("%d%d%d", &N, &M, &K);
    for(int i=0; i<K; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        lights[i]=pii(a,b);
        board[a][b]=1;
    }

    int ans=0;
    for(int l1=0; l1<K; ++l1)
    for(int x1=0; x1<4; ++x1)
    {
        memset(vis, 0, sizeof vis); seen[l1][x1]=1;
        int i, j; 
        i=lights[l1].first; j=lights[l1].second;
        dfs(l1,x1,i,j,x1); memcpy(vis1, vis, sizeof vis);
        for(int l2=l1+1; l2<K; ++l2)
        for(int x2=0; x2<4; ++x2) if (!seen[l2][x2])
        {
            memset(vis, 0, sizeof vis); seen[l2][x2]=1;
            i=lights[l1].first; j=lights[l1].second;
            dfs(l2, x2, i, j, x2);
            memcpy(vis2, vis, sizeof vis);
        }

        bool overlap=false;
        int curr=0;
        for(int i=0; i<N; ++i)
        for(int j=0; j<M; ++j)
        {
            if (vis1[i][j] && vis2[i][j]) overlap=true;
            if (board[i][j] && (vis1[i][j] || vis2[i][j]))
                curr++;
        }
        if (overlap) ans = max(ans, curr);
    }
    printf("%d\n", ans);
}
