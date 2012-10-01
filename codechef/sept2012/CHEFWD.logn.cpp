// =========================================================
// 
//       Filename:  CHEFWD.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/CHEFWD
// 
//        Version:  1.0
//        Created:  09/02/2012 10:32:03 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/02/2012, LI YAN
// 
// =========================================================

//
//
// the counting is done by using -1 as a splitter in the sequence
// then before -1, the sum is from 1 to N-1, inclusive
// after that, if we have a -1, then the second half sum is (pre+1)
// else we have a -2, then the second half sum is (pre+2)
//
// Now the counting is by multiply pre and post sums, using fibo to achieve
// the two sums
//
// g[n] = sum_j=1^(n-1) f[j] * f[n-j+1] + sum_j=1^(n-1) f[j] * f[n-j+2]
//      = sum_j=1^(n-1) f[j] * f[n+3-j]
//
// by g[n] - g[n-1], we have a linear recurrence
// g[1] = 0; g[2] = 5
// g[n] = g[n-1] + g[n-2] + f[n-1]*f[4] + f[n-2]*f[3] for n>=3
//
// but there has to be a way to solve it in log(n) time as n could be 10^15
//
// submitted and got TLE, as expected
// OK, so here is the trick
//
// g(n)   |    | 1 1 f[4] f[3] |  g(n-1)
// g(n-1) |  = | 1 0 0    0    |  g(n-2)
// f(n)   |    | 0 0 1    1    |  f(n-1)
// f(n-1) |    | 0 0 1    0    |  g(n-2)
//
// this can be solved in log(n) time using matrix fast pow
//
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;
const int MOD = 1e9+7;

const int pre[][4] = {
    {1, 1, 5, 3}, // 1, 1, fibo[4], fibo[3]
    {1, 0, 0, 0},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
};

int factor[55][4][4];

int add(int a, int b)
{
    return ((int64)a+b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a * b % MOD;
}

void matmult(const int a[][4], const int b[][4], int c[][4])
{
    const int dim = 4;
    for(int i=0; i<dim; ++i)
    for(int j=0; j<dim; ++j)
        c[i][j] = 0;
    for(int i=0; i<dim; ++i)
    for(int j=0; j<dim; ++j)
    for(int k=0; k<dim; ++k)
        c[i][j] = add(c[i][j], mult(a[i][k], b[k][j]));
}

void matpow(const int a[][4], int64 b, int c[][4])
{
    const int dim = 4;
    //int f[4][4],
    int tmp[4][4];
    for(int i=0; i<dim; ++i)
    for(int j=0; j<dim; ++j)
        c[i][j] = (i==j);

    //memcpy(f, a, sizeof f);
    int k=0;
    while(b) {
        if (b&1) { 
            matmult(c, factor[k], tmp);
            memcpy(c, tmp, sizeof tmp);
        }
        //matmult(f, f, tmp);
        //memcpy(f, tmp, sizeof tmp);
        b/=2; k++;
    }
}

void init()
{
    memcpy(factor[0], pre, sizeof pre);
    for(int k=1; (1LL<<k)<1e15; ++k) {
        matmult(factor[k-1], factor[k-1], factor[k]);
    }
}

void solve()
{
    int64 N; assert(scanf("%lld", &N)==1);
    int g[3], f[3];
    g[1] = 0; g[2] = 5;
    f[1] = 1; f[2] = 2;

    if (N==1) { printf("%d\n", g[1]); return; }
    if (N==2) { printf("%d\n", g[2]); return; }
    int prepow[4][4];
    matpow(pre, N-2, prepow);

    int ans = 0;
    ans = add(ans, mult(prepow[0][0], g[2]));
    // since g[1] = 0
    // ans = add(ans, mult(prepow[0][1], g[1])); 
    ans = add(ans, mult(prepow[0][2], f[2]));
    // since f[1] = 1
    // ans = add(ans, mult(prepow[0][3], f[1]));
    ans = add(ans, prepow[0][3]);

    printf("%d\n", ans);
}

int main()
{
    init();
    int T; assert(scanf("%d", &T) == 1);
    for(int i=0; i<T; ++i) {
        solve();
    }
}

// TLE
// T = 10^4
// N = 10^15

// previously failed idea
// use +1, +2 and one of -1 or -2 to sum up to N
// N = 10^15
// 
// let f[n] be the number of ways to make length = n, no use of -1
// let g[n] be number of ways to make length = n, use exactly once
// -1 or -2
//
// f[n] is fibo[n]
// g[n] a seq is split by -1 or -2
//
// g[n] is number of seq to get to pos=n with exactly 1 reverse
// f[n] if fibo
//
// g[n] = g[n-1] + g[n-2] + f[n+1] + f[n+2] = g[n-1] + g[n-2] + f[n+3]
// last is +1, last is +2, last is -1, last is -2
//
// g[0] = (+1 then -1) + (+2 then -2) = 2
// g[-1] = 1, first +1, then -2
//
// f[0] = 1
// f[1] = 1
// f[2] = 2
// f[3] = 3
// f[4] = 5
// f[5] = 8
// f[6] = 13
//
// ans is g[n] - f[n+3]
//
// g[n]      | 1 1 1 1 |  g[n-1]
// g[n-1]    | 1 0 0 0 |  g[n-2]
// f[n+3]  = | 0 0 1 1 |  f[n+2]
// f[n+2]    | 0 0 1 0 |  f[n+1]
//
// g[1] = g[0] + g[-1] + f[4] = 2 + 1 + 5 = 8
// g[2] = g[1] + g[0] + f[5] = 8 + 2 + 8 = 18 
// g[3] = g[2] + g[1] + f[6] = 18 + 8 = 26 
// g[4] = g[3] + g[2] + f[7] = 26 + 18 = 44
//
//
