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
int M, N;

int diff[][2] = {{-2, -2}, {-2, +2}, {+2, +2}, {+2, -2}};

bool inbound(int r, int c)
{
    return 0<=r && r<M && 0<=c && c<N;
}

/*
bool augment(int r, int c)
{
    vis[r][c] = 1;
    for(int x=0; x<4; ++x) {
        int r1, c1, r2, c2;
        r1 = r + diff[x][0]/2;
        c1 = c + diff[x][1]/2;
        r2 = r + diff[x][0];
        c2 = c + diff[x][1];
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
}  */

// BFS augment
int dist[705][705];
pii pred[705][705];
bool augment(int r, int c)
{
    for(int i=0; i<M; ++i)
    for(int j=0; j<N; ++j)
    {
        dist[i][j]=-1;
        pred[i][j]=pii(-1,-1);
    }
    queue<pii> que;
    que.push(pii(r,c)); dist[r][c]=0;
    pii plast=pii(-1,-1);
    while(!que.empty()) {
        pii top = que.front(); que.pop();
        int r0, c0;
        r0 = top.first; c0 = top.second;

        if (dist[r0][c0]&1) { // odd dist, follow mate
            assert(mate[r0][c0].first >= 0);
            {
                int r1, c1;
                r1 = mate[r0][c0].first;
                c1 = mate[r0][c0].second;
                if (dist[r1][c1]<0) {
                    dist[r1][c1] = dist[r0][c0]+1;
                    pred[r1][c1] = pii(r0,c0);
                    que.push(pii(r1,c1));
                }
            }
        }
        else { // even dist, follow edge to expand neighbor
        for(int x=0; x<4; ++x) {
            int r1, c1, r2, c2;
            r1 = r0 + diff[x][0]/2;
            c1 = c0 + diff[x][1]/2;
            r2 = r0 + diff[x][0];
            c2 = c0 + diff[x][1];
            if (inbound(r2,c2) && 
                grid[r1][c1]!='P' && 
                nodes[r2][c2] &&
                dist[r2][c2] < 0) { // (r,c) and (r2,c2) conflict iff both are 'F'
                                 // and no 'G' attacks them
                                 // and no 'P' in between
                
                dist[r2][c2] = dist[r0][c0] + 1;
                pred[r2][c2] = pii(r0,c0);
                que.push(pii(r2,c2));
                if (mate[r2][c2].first < 0) {
                    plast = pii(r2,c2);
                    goto done;
                }
            }
        }
        }
    }
    done:
    if (plast.first <0) return false;
    r = plast.first; c = plast.second;
    while(r>=0) {
        int r1, c1;
        r1 = pred[r][c].first;
        c1 = pred[r][c].second;
        plast = mate[r1][c1];
        mate[r1][c1] = pii(r,c);
        mate[r][c] = pii(r1,c1);
        r = plast.first;
        c = plast.second;
    }
    return true;
}

int main()
{
    while(1) {
        scanf("%d%d ", &M, &N);
        if (M==0 && N==0) break;
        for(int i=0; i<M; ++i)
            gets(grid[i]);
        
        //memset(nodes, 0, sizeof nodes);
        // find all F nodes
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            if (grid[i][j]=='F') nodes[i][j]=1;
            else nodes[i][j]=0;

        // kill F nodes not protected
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            if (grid[i][j]=='G') {
                for(int x=0; x<4; ++x) {
                    int r1, c1, r2, c2;
                    r1 = i + diff[x][0]/2;
                    c1 = j + diff[x][1]/2;
                    r2 = i + diff[x][0];
                    c2 = j + diff[x][1];

                    if (inbound(r2,c2) && 
                        grid[r2][c2]=='F' &&
                        grid[r1][c1]!='P') {
                            nodes[r2][c2]=0;
                        }
                }
            }

        int ans=0;
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            ans += nodes[i][j];

        //printf("all %d\n", ans);
        //memset(mate, -1, sizeof mate);
        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
            mate[i][j] = pii(-1,-1);

        for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j) 
        if (nodes[i][j] && mate[i][j].first<0) {
            //DFS init
            //for(int i2=0; i2<M; ++i2)
            //for(int j2=0; j2<N; ++j2)
            //    vis[i2][j2]=0;
            if (augment(i,j)) ans--;
        }

        printf("%d\n", ans);
    }
}

// TLE
