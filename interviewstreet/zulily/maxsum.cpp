// =========================================================
// 
//       Filename:  maxsum.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/16/2012 12:03:06 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/16/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int a[200000+5];

void solve()
{
    int N; scanf("%d", &N);
    int l, r, k;
    l=0; r=N+1; k=1;
    while(k<=N) {
        a[++l]=k;
        if (k+1<=N) a[--r]=k+1;
        k+=2;
    }
    long long ans=0;
    for(int i=1; i<N; ++i) ans += (long long)a[i]*a[i+1];
    printf("%lld\n", ans);
}
int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}
