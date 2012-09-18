// =========================================================
// 
//       Filename:  bilateral.cpp
// 
//    Description:  http://www.spotify.com/us/jobs/tech/bilateral-projects/
// 
//        Version:  1.0
//        Created:  09/15/2012 09:55:27 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2012, LI YAN
// 
// =========================================================

// min vertex cover in bipartite graph
// |VC| = |M|
// proof: 1. |VC| >= |M| because each (u,v) in M needs at least one vertex in VC
// 2. |VC| <= |M|, from M we can construct a set VC. For each (u,v) in M, we
// claim at most one of u,v has non-matched neighbor in E, because we would have
// an augment path if both have non-matched neighbor. Choose u or v with
// non-matched neighbor, if neither, choose anyone in the two.
//
// while there is a free vertex
// 1. pick free vertex w
// 2. start from w, do dfs, all dist=odd vertices in ans[]
//
// collect one side

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const int DD = 1000;
const int FF = 1009-DD;
// map id to id-1000
bool edge[2000][2000];
int adj[2000][1000]; // adj[i][x] = j if (i,j) is an edge
int cnt[2000];
int mate[2000];
int vis[2000];

bool augment(int s)
{
    vis[s] = 1;
    for(int x=0; x<cnt[s]; ++x) {
        int next = adj[s][x];
        if (mate[next]<0) {
            mate[s]=next; mate[next]=s;
            return true; 
        } else {
            int snew = mate[next];
            if (!vis[snew] && augment(snew)) {
                mate[s] = next; mate[next] = s;
                return true;
            }
        }
    }
    return false;
}

int bipartite_match()
{
    memset(mate, -1, sizeof mate);
    int match = 0;
    for(int i=0; i<DD; ++i) if (mate[i] < 0) {
        memset(vis, 0, sizeof vis);
        if (augment(i)) match++;
    }
    return match;
}

void dfs(int s, int d, int *&ans)
{
    vis[s] = 1;
    if (d&1) {
        *ans++ = s;
        // use M
        int next = mate[s];
        assert(next>=0);
        if (!vis[next]) dfs(next, d+1, ans);
    } else {
        for(int x=0; x<cnt[s]; ++x) {
            int next = adj[s][x];
            if (mate[next] != s && !vis[next]) {
                dfs(next, d+1, ans);
            }
        }
    }
}

void get_vc(int *ans)
{
    memset(vis, 0, sizeof vis);
    for(int i=0; i<DD; ++i) if (mate[i]<0) {
        dfs(i, 0, ans);
    }
    for(int i=0; i<DD; ++i) if (mate[i]>=0 && !vis[i]) {
        *ans++ = i;
    }
}

void build_graph()
{
    memset(cnt, 0, sizeof cnt);
    for(int i=0; i<2*DD; ++i)
    for(int j=0; j<2*DD; ++j)
        if (edge[i][j])
            adj[i][cnt[i]++] = j;
}

int main()
{
    int m; scanf("%d", &m);
    for(int i=0; i<m; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        a -= DD; b -= DD;
        edge[a][b] = edge[b][a] = true;
    }
    build_graph();
    int nmatch, friend_match;
    int ans1[2000]; // without friend
    int ans2[2000]; // with friend
    nmatch = bipartite_match(); printf("%d\n", nmatch);
    get_vc(ans1);

    // remove edges on FF and its neighbors
    for(int x=0; x<cnt[FF]; ++x) {
        int next = adj[FF][x];
        edge[FF][next] = edge[next][FF] = false;
    }
    build_graph();
    friend_match = bipartite_match(); //printf("%d\n", friend_match);
    get_vc(ans2);
    if (friend_match < nmatch) {
        assert(friend_match + 1 == nmatch);
        for(int i=0; i<friend_match; ++i) {
            printf("%d\n", ans2[i]+DD);
        }
        printf("%d\n", FF+DD);
    } else {
        assert(friend_match == nmatch);
        for(int i=0; i<nmatch; ++i) {
            printf("%d\n", ans1[i]+DD);
        }
    }
}


// Accepted
