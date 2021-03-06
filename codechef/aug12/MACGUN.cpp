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
int num[705][705];
int nodes[705][705]; // avail if 1
int mate[130000]; // default to (-1, -1)
int vis[130000];
int visst[130000]; // 130000 = 700*700/4
int viskk;
int M, N;
int ans=0;
int N1, N2;
int ecnt[130000];
int edge[130000][4];

int diff[][2] = {{-1, -1}, {-1, +1}, {+1, +1}, {+1, -1}};

bool inbound(int r, int c)
{
    return 0<=r && r<M && 0<=c && c<N;
}

bool augmentSimple(int s)
{
    for(int x=0; x<ecnt[s]; ++x) { // save from 6s to 3.7s
        int next = edge[s][x];
        if (mate[next]< 0) {
            mate[s] = next;
            mate[next] = s;
            return true;
        }
    }
    return false;
}

bool augment(int s) {
    vis[s] = 1; visst[viskk++] = s;
    for(int x=0; x<ecnt[s]; ++x) {
        int next = edge[s][x];
        if (mate[next]< 0) {
            mate[s] = next;
            mate[next] = s;
            return true;
        }
        int third = mate[next];
        if (!vis[third] && augment(third)) {
            mate[s] = next;
            mate[next] = s;
            return true;
        }
    }
    return false;
} 

// first : 0 even, 1 odd
// second: 0 even, 1 odd
void solve(int first, int second)
{
    N1=N2=0;
    // construct graph
    for(int i=first; i<M; i+=4)
    for(int j=second; j<N; j+=2)
        if (nodes[i][j]) { num[i][j] = N1++; }
    for(int i=first+2; i<M; i+=4)
    for(int j=second; j<N; j+=2)
        if (nodes[i][j]) { num[i][j] = N2++; }

    for(int x=0; x<N1+N2; ++x) { ecnt[x] = 0; mate[x] = -1; }

    for(int i=first; i<M; i+=4)
    for(int j=second; j<N; j+=2) 
        if (nodes[i][j]) {
            for(int x=0; x<4; ++x) {
                int r1, c1, r2, c2;
                r1 = i+diff[x][0];
                c1 = j+diff[x][1];
                r2 = r1+diff[x][0];
                c2 = c1+diff[x][1];

                if (inbound(r2,c2) && nodes[r2][c2] &&
                    grid[r1][c1]!='P') {
                        int ll, rr;
                        ll = num[i][j]; rr = N1+num[r2][c2];
                        edge[ll][ecnt[ll]++] = rr;
                        edge[rr][ecnt[rr]++] = ll;
                    }
            }
        }

    for(int x=0; x<N1; ++x) if (mate[x]<0) {
        if (augmentSimple(x)) ans--;
    }
    for(int x=0; x<N1; ++x) if (mate[x]<0) {
        //for(int i=0; i<N1+N2; ++i) vis[i]=0;
        viskk = 0;
        if (augment(x)) ans--;
        // only reset nodes visited by previous DFS
        for(int x=0; x<viskk; x++)
            vis[visst[x]]=0;
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


        // solve 4 components separately
        // (odd, odd), (odd, even), (even, odd), (even, even)
        for(int first=0; first<=1; first++)
        for(int second=0; second<=1; second++) {
            solve(first, second);
        }
        printf("%d\n", ans);
    }
}

// Correct Answer
// Execution Time: 33.00
//
// TLE
// for 300x300 graph with all 'F'
// laycurse implementation: 0.022s
// he avoids (r,c) pair completely
//
// my implementation
// with 4 component, 23s
// with dfs only reset visited nodes, 8s
// 
// seems the key is to map (r,c) to N1, N2
// and maintain edgelist for each vertex
// 
// this is the last optimization to get AC
// 2. reset only visited dfs entry
//
// other tricks are not essential
// like 
// 1. manually inline inbound function
//
