// =========================================================
// 
//       Filename:  datacenter.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/07/2012 11:40:47 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/07/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

typedef long long int64;

const int MOD = 1000000000+7;
const int MAX = 10;
int table[MAX+2];

int add(int a, int b)
{
    return ((int64)a+b)%MOD;
}

int mult(int a, int b)
{
    return (int64)a*b %MOD;
}

int fastpow(int a, int n)
{
    int ans=1;
    int b=a;
    while(n) {
        if (n&1) ans = mult(ans, b);
        n/=2;
        b = mult(b, b);
    }
    return ans;
}

int main()
{
    for(int i=2; i<=MAX; ++i)
    for(int j=2; j<=i; ++j) {    
        printf("i %d j %d\n", i, j);
        table[i] = add(table[i], fastpow(j, i-j));
    }

    puts("done");
    int T; scanf("%d", &T);
    while(T--) {
        int n; scanf("%d", &n);
        if (n<=MAX) printf("%d\n", table[n]);
        else { /* not implemented */ }
    }
}
