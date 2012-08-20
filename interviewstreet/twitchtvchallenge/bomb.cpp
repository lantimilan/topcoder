// =========================================================
// 
//       Filename:  bomb.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/05/2012 03:27:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      CopyR:  CopyR (c) 05/05/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

int N, M;
int edge[500][500];
int L[500], R[500];
int myprev[500];
int vis[500];

int dfs(int s)
{
    vis[s]=1;
    for(int j=N; j<N+M; ++j) {
        if (edge[s][j]) {
            if (R[j] < 0) { myprev[j]=s; return j; }
            else {
                int next = R[j];
                if (vis[next]) continue;
                int res = dfs(next);
                if (res>=0) { myprev[j]=s; return res; }
            }
        }
    }
    return -1;
}

bool augment(int s)
{
    memset(vis, 0, sizeof vis);
    memset(myprev, -1, sizeof myprev);
    int last;
    if ((last=dfs(s))>=0) {
        assert(R[last]<0);
        int x=last;
        while(x>=0) {
            R[x] = myprev[x];
            int tmp = L[myprev[x]];
            L[myprev[x]]=x;
            x=tmp;
        }
        return true;
    }
    else return false;
}

int main()
{
    cin >> N >> M;
    memset(edge, 0, sizeof edge);
    for(int i=0; i<N; ++i)
    for(int j=0; j<M; ++j)
        cin >> edge[i][j+N];       

    int ans=0;
    memset(L, -1, sizeof L);
    memset(R, -1, sizeof R);
    while(true) {
        bool update=false;
        for(int i=0; i<N; ++i) if (L[i]<0) {
            if (augment(i)) { update=true; ans++; }
        }
        if (!update) break;
    }
    cout << ans << endl;
}

// Super Bomb   cpp     2012-05-06 04:19:43     Processed   Accepted
// Score: 100
//  View Details
