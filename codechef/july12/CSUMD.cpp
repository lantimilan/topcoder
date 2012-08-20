// =========================================================
// 
//       Filename:  CSUMD.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/01/2012 09:15:39 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;
// fast matrix mult
const int mat[][2] = {{2,2}, {1,0}};
const int MOD = 1000000007;

int modadd(int a, int b)
{
    return ((int64)a+b) % MOD;
}
int modmult(int a, int b)
{
    return (int64)a*b % MOD;
}

void mult(const int m1[][2], const int m2[][2], int m3[][2])
{
    for(int i=0; i<2; ++i)
    for(int j=0; j<2; ++j)
        m3[i][j]=0;
    for(int i=0; i<2; ++i)
    for(int j=0; j<2; ++j)
    for(int k=0; k<2; ++k)
        m3[i][j] += modmult(m1[i][k], m2[k][j]);
}

void mcopy(int dest[][2], const int src[][2])
{
    for(int i=0; i<2; ++i)
    for(int j=0; j<2; ++j)
        dest[i][j] = src[i][j];
}

void fastpow(const int m[][2], int n, int mout[][2])
{
    mout[0][0]=mout[1][1]=1;
    mout[0][1]=mout[1][0]=0;

    int factor[2][2];
    int tmp[2][2];
    mcopy(factor, m);
    while(n) {
        if (n&1) { 
            mult(mout, factor, tmp); 
            mcopy(mout, tmp);
        }
        n/=2;
        mult(factor, factor, tmp);
        mcopy(factor, tmp);
    }
}

void solve()
{
    int N; scanf("%d", &N);
    int g[10];
    int pre[2][2];

    if (N==1) { printf("%d\n", 1); return; }
    g[0]=1; g[1]=2;
    fastpow(mat, N-2, pre);
    int t1=0, t2=0;
    t1 = modadd(modmult(pre[0][0],g[1]), modmult(pre[0][1], g[0]));
    t2 = modadd(modmult(pre[1][0],g[1]), modmult(pre[1][1], g[0]));
    int ans = modadd(t1, t2);
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}
