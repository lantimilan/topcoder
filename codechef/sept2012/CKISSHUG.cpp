// =========================================================
// 
//       Filename:  CKISSHUG.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/CKISSHUG
// 
//        Version:  1.0
//        Created:  09/01/2012 08:34:49 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

const int MOD = 1000000000+7;

int mypow(int a, int b)
{
    int ans = 1;
    long long f = a;
    while(b) {
        if (b&1) ans = (ans * f) % MOD;
        b /= 2;
        f = (f * f) % MOD;
    }
    return ans;
}

int main()
{
    int T; scanf("%d", &T);
    for(int i=0; i<T; ++i) {
        int N; scanf("%d", &N);
        int K = N/2;
        // ans = f[0] + sum_i=1^N 2^(i/2)
        // ans = 2^(K+1) + 2^K - 2 + (2^K if odd)
        int ans;
        ans = ((long long)mypow(2,K+1) + mypow(2,K)) % MOD;
        if (ans == 0) ans = MOD;
        ans-=2;
        if (N&1) ans = ((long long)ans + mypow(2,K)) % MOD;
        printf("%d\n", ans);
    }

    // only the first kiss needs to be propagated
    // try first pos: if H, then f[N-1], else K, then only N/2 pos
    // and those pos can be either one of the two
    //
    // f[0]=1;
    // f[N] = f[N-1] + 2^N/2
    // f[N] = 2^(N/2) + 2^(N-1)
}

