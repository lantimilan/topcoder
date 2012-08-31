// =========================================================
// 
//       Filename:  prob187B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/10/2012 08:43:37 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/10/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

int dp[65][65][1005];
int single[65][65];
int edge[65][65][65];
int N, M, K, R;
const int MAX=1000000000;

void chmin(int &a, int b)
{
    a=a<b?a:b;
}

void allshortest()
{
    // init to MAX
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
    for(int k=0; k<K; ++k)
        dp[i][j][k] = MAX;

    // dp[][][0]
    for(int c=0; c<M; ++c)
    {
    for(int s=0; s<N; ++s)
    for(int t=0; t<N; ++t)
        single[s][t] = edge[s][t][c];

    for(int x=0; x<N; ++x)
    for(int s=0; s<N; ++s)
    for(int t=0; t<N; ++t)
        chmin(single[s][t], single[s][x]+single[x][t]);

    for(int s=0; s<N; ++s)
    for(int t=0; t<N; ++t)
        chmin(dp[s][t][0], single[s][t]);
    }

    for(int k=1; k<=K; ++k)
    for(int s=0; s<N; ++s)
    for(int t=0; t<N; ++t)
        dp[s][t][k] = dp[s][t][0];

    for(int k=1; k<=K; ++k)
    for(int x=0; x<N; ++x)
    for(int s=0; s<N; ++s)
    for(int t=0; t<N; ++t)
    {
        chmin(dp[s][t][k], dp[s][x][0]+dp[x][t][k-1]);
    }
}

int main()
{
    scanf("%d%d%d", &N, &M, &R); K=1000;
    for(int c=0; c<M; ++c)
    for(int i=0; i<N; ++i)
    for(int j=0; j<N; ++j)
        scanf("%d", &edge[i][j][c]);

    allshortest();
    for(int r=0; r<R; ++r) {
        int a, b, k; scanf("%d%d%d", &a, &b, &k);
        --a; --b;
        printf("%d\n", dp[a][b][k]);
    }
}
