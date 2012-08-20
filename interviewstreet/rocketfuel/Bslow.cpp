// =========================================================
// 
//       Filename:  Bslow.cpp
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

#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int N, M, K;
int board[1605][1605];
int vis[1605][1605][4];
pii lights[10005];
set<pii> hits[10005][4];

int dir[][2]={{-1,-1}, {-1,+1}, {+1,+1}, {+1,-1}};

void dfs(int l, int start, int r, int c, int x)
{
    vis[r][c][x]=1; if (board[r][c]) hits[l][start].insert(pii(r,c));
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
    if (!vis[r2][c2][x]) dfs(l,start,r2,c2,x);
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
    for(int l=0; l<K; ++l)
    {
        for(int x=0; x<4; ++x)
        {
            int i, j; i=lights[l].first; j=lights[l].second;
            memset(vis, 0, sizeof vis);
            dfs(l,x,i,j,x);
            //printf("(%d,%d) x=%d %d\n", i,j,x, hits[l][x].size());
        }
        for(int a=0; a<4; ++a)
        for(int b=a+1; b<4; ++b) {
            set<pii> inter=hits[l][a];
            set<pii>::iterator it;
            for(it=hits[l][b].begin(); it!=hits[l][b].end(); ++it)
                inter.insert(*it);
            ans = max(ans, int(inter.size()));
        }
    }
    printf("%d\n", ans);
}
