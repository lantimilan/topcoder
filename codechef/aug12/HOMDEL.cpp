// =========================================================
// 
//       Filename:  HOMDEL.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/HOMDEL
// 
//        Version:  1.0
//        Created:  08/01/2012 09:05:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

int N, M;
int T[260][260];
int dist[260][260];

void chmin(int &a, int b)
{
    a=a<b?a:b;
}

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j) {
        scanf("%d", &T[i][j]);
        dist[i][j] = T[i][j];
    }

    // floyd-warshall
    for(int k=0; k<N; ++k)
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        chmin(dist[i][j], dist[i][k] + dist[k][j]);

    scanf("%d", &M);
    for(int m=0; m<M; ++m) {
        int S, G, D; scanf("%d%d%d", &S, &G, &D);
        int time = dist[S][G] + dist[G][D];
        int ans;
        ans = time - dist[S][D];
        printf("%d %d\n", time, ans);
    }
}
