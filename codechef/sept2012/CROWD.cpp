// =========================================================
// 
//       Filename:  CROWD.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/CROWD
// 
//        Version:  1.0
//        Created:  09/01/2012 10:39:15 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/01/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1000000000+7;

void refadd(int &a, int b)
{
    a = ((long long)a + b) % MOD;
}

int mult(int a, int b)
{
    return (long long)a * b % MOD;
}

int intpow(int a, long long b)
{
    b %= (MOD-1);
    int ans = 1;
    int f = a;
    while(b) {
        if (b&1) ans = mult(ans, f);
        b /= 2;
        f = mult(f, f);
    }
    return ans;
}

void matmult(const int a[][3], const int b[][3], int c[][3])
{
    const int dim = 3;
    for(int i=0; i<dim; ++i)
    for(int j=0; j<dim; ++j)
        c[i][j] = 0;
    for(int i=0; i<dim; ++i)
    for(int j=0; j<dim; ++j)
    for(int k=0; k<dim; ++k)
        refadd(c[i][j], mult(a[i][k], b[k][j]));
}

void matpow(const int a[][3], long long b, int c[][3]) 
{
//    b %= (MOD-1); no Fermat's theorem here
//    not for matrix pow
    int f[3][3], tmp[3][3];
    memcpy(f, a, sizeof f);
    for(int i=0; i<3; ++i)
    for(int j=0; j<3; ++j)
        c[i][j] = (i==j);
    while(b) {
        if (b&1) { 
            matmult(f, c, tmp);
            memcpy(c, tmp, sizeof tmp);
        }
        b /= 2;
        matmult(f, f, tmp);
        memcpy(f, tmp, sizeof tmp);
    }
}

int calcGN(long long N)
{
    int vec[] = {1, 1, 2};
    if (N<3) return vec[N];

    int base[3][3] = {
        {1, 1, 1},
        {1, 0, 0},
        {0, 1, 0}};
    int pre[3][3];
    matpow(base, N-2, pre);
    int ans = mult(pre[0][0], vec[2]);
    refadd(ans, mult(pre[0][1], vec[1]));
    refadd(ans, mult(pre[0][2], vec[0]));
    return ans;
}

int main()
{
    int T; scanf("%d", &T);
    for(int i=0; i<T; ++i) {
        long long N; scanf("%lld", &N);
        if (N<=2) {
            int ans = 0;
            printf("%d\n", ans);
            // very dumb, I wrote return 0
            // here so all the rest test cases
            // are skipped
        }
        else {
            assert(N>=3);
            //f[N] = g[N-2] + g[N-1]
            //ans = 2^N - (f[N] + g[N]) 
            //= 2^N - (g[N] + g[N-1] + g[N-2])
            //= 2^N - g[N+1]
            int ans;
            ans = calcGN(N+1);
            ans = intpow(2, N) - ans;
            if (ans < 0) ans += MOD;
            printf("%d\n", ans);
        }
    }
}

// with Fermat's theorem on integer pow
// 306170   1 min ago       13.79   2.6M    C++ 4.3.2   
//
// without Fermat's theorem on integer pow
// 1306162  3 min ago       13.94   2.6M    C++ 4.3.2
//
// after remove Fermat's trick for matrix mult, finally got AC
// Correct Answer
// Execution Time: 13.94
//
// we count valid seq instead, that is, seq with no triples of 1
// let f(N) be number of valid seq with last being 1
// g(N) be number of valid seq with last being 0
// then
// f(N) = g(N-2) + g(N-1) // N-1 is 1 then N-2 must be 0, plus N-1 is 0
// g(N) = f(N-1) + g(N-1) // if N is 0, then N-1 can be anything
//
// g(N) = g(N-1) + g(N-2) + g(N-3)
// this can be computed using matrix fast pow
//
// g(N)     | 1 1 1 |   | g(N-1) |
// g(N-1) = | 1 0 0 | * | g(N-2) |
// g(N-2)   | 0 1 0 |   | g(N-3) |
//
// no TLE but WA now
// still TLE even after Fermat's theorem
