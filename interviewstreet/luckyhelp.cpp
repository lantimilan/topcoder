// =========================================================
// 
//       Filename:  test.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/06/2012 08:39:06 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/06/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;

int sqr[1600][20];
long long cnt[1600][20];

long long count(int n, int p)
{
    if (p<0) return 0;
    if (n==0) return p>=0;
    if (cnt[n][p]>=0) return cnt[n][p];
    long long &ans=cnt[n][p]; ans=0;
    for(int x=min(int(sqrt(n)+1.0e-8),9); x>=0; --x) {
        ans += count(n-x*x, p-1);
    }
    return ans;
}

int issqr(int n, int p)
{
    if (sqr[n][p]>=0) return sqr[n][p];
    if (p>=18) return n==0;
    for(int d=0; d<9 && d<=n; ++d) {
        if (issqr(n-d,p+1)) return sqr[n][p]=1;
    }
    return sqr[n][p]=0;
}

int main()
{
    bool isprime[1600];
    int vec[1600]; int nvec=0;
    for(int i=0; i<1600; ++i) isprime[i]=true;
    isprime[0]=isprime[1]=false;
    for(int i=2; i<1600; ++i) if (isprime[i]) {
        for(int j=i*i; j<1600; j+=i) isprime[j]=false;
    }
    int primes[1600], nprime=0;
    for(int i=0; i<1600; ++i) if (isprime[i]) {
        primes[nprime++]=i;
    }
    for(int i=0; i<nprime; ++i) printf("%d ", primes[i]);
    putchar('\n');

    memset(sqr,-1,sizeof sqr);
    for(int i=0; i<nprime; ++i) if (issqr(primes[i],0)) { 
        printf("%d ", primes[i]);
        vec[nvec++]=primes[i];
    }
    putchar('\n');

    memset(cnt, -1, sizeof cnt);
    long long total=0;
    for(int i=0; i<nvec; ++i) {
        long long d = count(vec[i],18);
        printf("%d: %lld\n", vec[i], d);
        total += d;
    }
    printf("total %lld\n", total);
}
