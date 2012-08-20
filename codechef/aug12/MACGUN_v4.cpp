// =========================================================
// 
//       Filename:  MACGUN.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/MACGUN
// 
//        Version:  1.0
//        Created:  08/05/2012 09:13:43 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/05/2012, LI YAN
// 
// =========================================================

// max indepdent set (stable set) in bipartite graph
// edge[(r1,c1)][(r2,c2)] = 1 if (r1,c1) hits (r2,c2)
//
#include <cassert>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

char grid[705][705];
int nodes[705][705]; // avail if 1
pii mate[705][705]; // default to (-1, -1)
int vis[705][705];
pii visst[130000]; // 130000 = 700*700/4
int viskk;
int M, N;
int ans=0;

//int diff[][2] = {{-2, -2}, {-2, +2}, {+2, +2}, {+2, -2}};
int diff[][2] = {{-1, -1}, {-1, +1}, {+1, +1}, {+1, -1}};

bool inbound(int r, int c)
{
    return 0<=r && r<M && 0<=c && c<N;
}

bool augment(int r, int c)
{
    vis[r][c] = 1; visst[viskk++] = pii(r,c);
    for(int x=0; x<4; ++x) {
        int r1, c1, r2, c2;
        r1 = r + diff[x][0];
        c1 = c + diff[x][1];
        r2 = r1 + diff[x][0];
        c2 = c1 + diff[x][1];
        if (inbound(r2,c2) && 
            grid[r1][c1]!='P' && 
            nodes[r2][c2]) { // (r,c) and (r2,c2) conflict iff both are 'F'
                             // and no 'G' attacks them
                             // and no 'P' in between
            if (mate[r2][c2].first < 0) {
                mate[r][c] = pii(r2,c2);
                mate[r2][c2] = pii(r,c);
                return true;
            }
            else {
                int r3, c3;
                r3 = mate[r2][c2].first;
                c3 = mate[r2][c2].second;
                if (!vis[r3][c3] && augment(r3,c3)) {
                    mate[r][c] = pii(r2,c2);
                    mate[r2][c2] = pii(r,c);
                    return true;
                }
            }
        }
    }
    return false;
} 

// first : 0 even, 1 odd
// second: 0 even, 1 odd
void solve(int first, int second)
{
        for(int i=first; i<M; i+=4)
        for(int j=second; j<N; j+=2) {
        if (nodes[i][j] && mate[i][j].first<0) {
            viskk = 0;
            if (augment(i,j)) ans--;
            // only reset nodes visited by previous DFS
            for(int x=0; x<viskk; x++)
                vis[visst[x].first][visst[x].second] = 0;
        }
        }
}

int main()
{
    while(1) {
        scanf("%d%d ", &M, &N);
        if (M==0 && N==0) break;
        for(int i=0; i<M; ++i)
            gets(grid[i]);
        
        // find all F nodes
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j) {
            if (grid[i][j]=='F') nodes[i][j]=1;
            else nodes[i][j]=0;
        }

        // kill F nodes not protected
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            if (grid[i][j]=='G') {
                for(int x=0; x<4; ++x) {
                    int r1, c1, r2, c2;
                    r1 = i + diff[x][0];
                    c1 = j + diff[x][1];
                    r2 = r1 + diff[x][0];
                    c2 = c1 + diff[x][1];

                    if (inbound(r2,c2) && 
                        grid[r2][c2]=='F' &&
                        grid[r1][c1]!='P') {
                            nodes[r2][c2]=0;
                        }
                }
            }

        ans = 0; // multiple testcases, reset ans
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            ans += nodes[i][j];

        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j) {
            vis[i][j] = 0; // multiple test case, reset vis[M][N]
            mate[i][j] = pii(-1,-1);
        }

        // solve 4 components separately
        // (odd, odd), (odd, even), (even, odd), (even, even)
        for(int first=0; first<=1; first++)
        for(int second=0; second<=1; second++) {
            solve(first, second);
        }
        printf("%d\n", ans);
    }
}

// TLE
// for 300x300 graph with all 'F'
// laycurse implementation: 0.022s
// he avoids (r,c) pair completely
//
// my implementation
// with 4 component, 23s
// with dfs only reset visited nodes, 8s
// 
