// =========================================================
// 
//       Filename:  datacenter3.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2012 10:25:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2012, LI YAN
// 
// =========================================================

// not this sequence
#include <cstdio>
using namespace std;

typedef long long int64;

const int MOD = 1000000000+7;

int add(int a, int b)
{
    return ((int64)a+b)%MOD;
}

int mult(int a, int b)
{
    return (int64)a*b%MOD;
}

int fastpow(int a, int n)
{
    int ans=1;
    int b=a;
    while(n) {
        if (n&1) ans = mult(ans, b);
        n/=2;
        b=mult(b,b);
    }
    return ans;
}

int inv(int a, int p)
{
    return fastpow(a, p-2);
}

int comb(int a, int b)
{
    if (a<b) return 0;
    int ans=1;
    for(int i=a; i>b; --i)
        ans = mult(ans, i);
    for(int i=1; i<=b; ++i)
        ans = mult(ans, inv(i,MOD));
    return ans;
}

int main()
{
    /*
    for(int n=2; n<10; ++n) {
        int ans;
        ans = mult(comb(3*n, n), inv(2*n+1, MOD));
        printf("%d\n", ans);
    }
    */
    int ans[] = {1, 1, 1, 3, 12, 55, 273, 1428, 7752, 43263, 246675, 1430715};
    int n; scanf("%d", &n);
    printf("%d\n", ans[n]);
}
