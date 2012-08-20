// =========================================================
// 
//       Filename:  datacenter2.cpp
// 
//    Description:  solution from chhung6
// 
//        Version:  1.0
//        Created:  07/08/2012 09:17:20 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2012, LI YAN
// 
// =========================================================

// DP[N][M]: # of config with N servers and M clients
//
// N=1, it is (M+1)^(M+1-2) Cayley's formula for # of rooted labeled spanning
// tree
// N=2, it is sum_K=0^M (M choose K) as we can partition the M clients between 2
// servers
//
// in general, 
// DP[N][M] = sum_K=0^M  (M choose K) * DP[N-1][K] * (M-K+1)^(M-K+1-2)
// where we use K clients in the first N-1 servers and M-K clients in the N^th
// server
//

#include <cassert>
#include <cstdio>
using namespace std;

typedef long long int64;
const int N=100;
const int MOD=1000000000+7;
int dp[1003][1003];
int comb[1003][1003];

int add(int a, int b)
{
    return ((int64)a+b)%MOD;
}

int sub(int a, int b)
{
    return ((int64)a-b+MOD)%MOD;
}

int mult(int a, int b)
{
    return (int64)a*b%MOD;
}

void init()
{
    comb[0][0]=1;
    for(int i=1; i<N; ++i) {
        comb[i][0]=1;
        for(int j=1; j<=i; ++j) {
            comb[i][j]=add(comb[i-1][j], comb[i-1][j-1]);
        }
    }
}

int pow(int a, int n)
{
    int ans=1;
    if (a==1) return 1;
    assert(n>=0);
    int b=a;
    while(n) {
        if (n&1) ans = mult(ans, b);
        b = mult(b, b);
        n/=2;
    }
    return ans;
}

int inv(int a)
{
    return pow(a, MOD-2);
}

int main()
{
    init(); 
    for(int i=0; i<N; ++i)
        dp[i][0]=1;
    for(int i=1; i<N; ++i)
    for(int j=1; j<N; ++j)
    for(int k=0; k<=j; ++k) {
        //dp[i][j] += comb[j][k] * dp[i-1][k] * pow(j-k+1, j-k+1-2);
        int t = mult(comb[j][k], dp[i-1][k]);
        t = mult(t, pow(j-k+1, j-k+1-2));
        dp[i][j] = add(dp[i][j], t);
    }

    /*
     // A058128         a(1)=1, a(n)=(n^n-n)/(n-1)^2 for n >= 2. 
     // 2, 6, 28, 195, 1866, 22876, 342392, 6053445, 123456790
     //     
     //
     //     Number of acyclic-function digraphs on n vertices. An
     //     acyclic-function digraph is a labeled digraph which (i) has no
     //     cycles and no loops, (ii) has outdegree 0 or 1 for all vertices and
     //     (iii) has x > y when vertex x has outdegree 0 and vertex y has
     //     outdegree 1. 
    for(int n=2; n<N; n++) {
        int ans=0;
        for(int k=1; k<=n; ++k) {
            ans = add(ans, dp[k][n-k]);
        }
        printf("%d, ", ans);
    }
    putchar('\n');
    */
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n); // assert(n<N);
        int ans=0;
        ans = pow(n,n);
        ans = sub(ans, n);
        ans = mult(ans, inv(mult(n-1, n-1)));
        ans = sub(ans, pow(n, n-2));
        printf("%d\n", ans);
    }
}

// Accepted.
//
// this solution is from chhung6
// here is his original email
//
// Chun-Ho Hung
// 3:18amChun-Ho Hung
// Hi Li,
//
// Sure.
//
// Let's begin with a slower solution.
//
// Let N := # servers, M := # clients.
//
// When N = 1, the # possibilities = # spanning trees with (M+1) vertices. This
// number can be computed easily using the formula (M+1)^(M+1-2).
//
// When N = 2, we can have K of M clients connected to the 1st server, and the
// remaining M - K clients connected to the 2nd. We enumerate K = 0 via M: for
// each possible K, there is exactly C(M, K) choices to pick the K clients.
//
// In general, we let DP[N][M] := # possible configurations corresponding to N
// servers and M clients. The recurrence is very much the same as a
// knapsack/subset sum DP. In particular, DP[N][M] is updated using
// 1. DP[N-1][K]
// 2. formula for counting the number of spanning trees
// 3. C(N, K)
//
// Once we have computed this table, given an input X, the answer is DP[2][M-2]
// + DP[3][M-3] + ... + DP[X][0].
//
// However, the input range (X ~ 10^9) is too large. To work around this, we can
// only derive closed form solution, which can be found by googling the first
// few terms in the OEIS database. The sequence I searched was { DP[1][M-1] +
// DP[2][M-2] + ... DP[M][0] } for M = 2, 3, 4, 5, 6. (Actually I first
// misinterpreted the input range as X <= 109 instead of 10^9... thus get an RTE
// in the first trial.)
//
// Hope this helps.
