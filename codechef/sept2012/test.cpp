// =========================================================
// 
//       Filename:  test.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/2012 04:39:18 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/06/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

const int MOD = 1e9+7;
int g[1024];
int f[1024];

int add(int a, int b)
{
    return ((int64)a+b) % MOD;
}

int fibo(int n)
{
    int a, b;
    a=b=1;
    for(int i=2; i<=n; ++i) {
        int c = add(a,b);
        a=b; b=c;
    }
    return b;
}

int mult(int a, int b)
{
    return (int64)a * b % MOD;
}

int calc(int64 n)
{
    int a, b;
    if (n==1) return 0;
    a=0; b=5;
    for(int i=3; i<=n; ++i) {
        int c = add(a, b);
        c = add(c, mult(fibo(i-1), fibo(4)));
        c = add(c, mult(fibo(i-2), fibo(3)));
        a=b; b=c;
    }
    return b;
}

int main()
{
    /* 
    f[0] = f[1] = 1;
    for(int i=2; i<30; ++i) {
        f[i] = f[i-1] + f[i-2];
    }
    g[1] = 0; g[2] = 5;
    printf("%d %d", g[1], g[2]);
    for(int i=3; i<30; ++i) {
        g[i] = g[i-1] + g[i-2] + f[i-1]*f[4] + f[i-2]*f[3];
        printf(" %d", g[i]);
    }
    putchar('\n');
    */
    /*
    for(int i=1; i<30; ++i) {
        printf("%d ", calc(i));
    }
    putchar('\n');
    */
    int T; scanf("%d", &T);
    for(int i=0; i<T; ++i) {
        int64 N;
        scanf("%lld", &N);
        int ans = calc(N);
        printf("%d\n", ans);
    }
}
