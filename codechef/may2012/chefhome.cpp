// =========================================================
// 
//       Filename:  chefhome.cpp
// 
//    Description:  A Home for Chef
//
//    Problem code: CHEFHOME
// 
//        Version:  1.0
//        Created:  05/03/2012 08:41:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long int64;

int X[1005], Y[1005];

void solve()
{
    int N; scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%d%d", &X[i], &Y[i]);
    if (N&1) { printf("1\n"); return; }
    sort(X, X+N); sort(Y, Y+N);
    int64 dx = X[N/2] - X[N/2-1] +1;
    int64 dy = Y[N/2] - Y[N/2-1] +1;
    int64 ans = dx * dy;
    printf("%lld\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=1; t<=T; ++t) solve();
}
