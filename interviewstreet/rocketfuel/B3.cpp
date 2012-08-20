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
#include <map>
#include <set>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int N, M, K;
int board[1605][1605];
pii seen[10005][4]; // id, x
int vis[1605][1605];
set<int> hits[10005][4];
pii lights[10005];
map<pii, int> lookup; // (i,j), id

int dir[][2]={{-1,-1}, {-1,+1}, {+1,+1}, {+1,-1}};

void dfs(int l, int start, int r, int c, int x)
{
    vis[r][c]=1; 
    if (board[r][c]) { 
        int id=lookup[pii(r,c)]; 
        seen[id][x]=pii(l,start); 
        hits[l][start].insert(id);
    }
    int r2, c2;
    r2 = r+dir[x][0];
    c2 = c+dir[x][1];
    // bounce
    while(!(0<=r2 && r2<N && 0<=c2 && c2<M)) {
        x=(x+1)%4;
        r2+=dir[x][0];
        c2+=dir[x][1];
    }
    if (!vis[r2][c2]) dfs(l,start,r2,c2,x);
}

int main()
{
    scanf("%d%d%d", &N, &M, &K);
    for(int i=0; i<K; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        lights[i]=pii(a,b); lookup[pii(a,b)]=i;
        board[a][b]=1;
    }

    int ans=0;
    memset(seen, -1, sizeof seen);
    for(int l1=0; l1<K; ++l1)
    for(int x1=0; x1<4; ++x1) if (seen[l1][x1].first<0)
    {
        seen[l1][x1] = pii(l1,x1);
        memset(vis, 0, sizeof vis);
        int i, j; 
        i=lights[l1].first; j=lights[l1].second;
        dfs(l1,x1,i,j,x1);
    }
    for(int l=0; l<K; ++l)
    {
        for(int a=0; a<4; ++a)
        for(int b=a+1; b<4; ++b)
        {
            pii pa, pb;
            pa=seen[l][a];
            pb=seen[l][b];
            set<int> curr=hits[pa.first][pa.second];
            set<int> &sb=hits[pb.first][pb.second];
            for(set<int>::iterator it=sb.begin(); it!=sb.end(); ++it)
                curr.insert(*it);
            ans = max(ans, int(curr.size()));
        }
    }
    printf("%d\n", ans);
}
