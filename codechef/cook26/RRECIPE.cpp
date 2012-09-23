// =========================================================
// 
//       Filename:  RRECIPE.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2012 09:27:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;

const int MOD = 10000000+9;
const int M1 = 23;
const int M2 = 434783;
char recipe[1000000+5];

int primes[1000000];
bool isprime[1000000];
int P;

void factor(int n)
{
    printf("%d = ", n);
    for(int x=0; x<P; ++x) if (n%primes[x]==0) {
        int p=0;
        while(n%primes[x] == 0) { p++; n/=primes[x]; }
        printf("%d^%d ", primes[x], p);
    }
    putchar('\n');
}

void init()
{
    int n = 1000000;
    P=0;
    for(int i=2; i<n; ++i) isprime[i] = true;
    for(int i=2; i<n; ++i) if (isprime[i]) {
        primes[P++] = i;
        for(int j=i+i; j<n; j+=i) primes[j] = false;
    }
}

int add(int a, int b, int mod) {
    return ((int64)a+b) % mod;
}
int mult(int a, int b, int mod) {
    return (int64)a*b % mod;
}

int extgcd(int a, int b, int& x, int& y) {
    if (b==0) { x=1; y=0; return a; }
    int xx, yy;
    int g;
    g = extgcd(b, a%b, xx, yy);
    x = yy;
    y = xx - a/b*x;
    return g;
}

int inv(int n, int p) {
    int x, y;
    extgcd(n, p, x, y);
    while(x < 0) x+=p;
    return x;
}

int main()
{
    //init();
    //factor(MOD);
    int T; scanf("%d ", &T);
    while (T--) {
        gets(recipe);
        int n;
        int i, j;
        int ans=1;
        int ans1=1, ans2=1;
        n = strlen(recipe);
        for(i=0, j=n-1; i<=j; ++i, --j) {
            if (recipe[i] == '?' && recipe[j] == '?') { //ans *= 26;
                ans1 = mult(ans1, 26, M1);
                ans2 = mult(ans2, 26, M2);
            } else if (recipe[i] == '?' || recipe[j] == '?') { ans *= 1;
            } else {
                assert(recipe[i] != '?' && recipe[j] != '?');
                if (recipe[i] != recipe[j]) { ans = 0; break; }
            }
        }
        if (ans) {
            int v1, v2;
            v1 = inv(M1, M2); assert(v1>0 && mult(v1, M1, M2) == 1);
            v2 = inv(M2, M1); assert(v2>0 && mult(v2, M2, M1) == 1);
            ans = mult(ans, v1, MOD);
            ans = mult(ans, M1, MOD);
            ans = mult(ans, ans2, MOD);
            ans1 = mult(ans1, v2, MOD);
            ans1 = mult(ans1, M2, MOD);
            ans = add(ans, ans1, MOD);
        }
        printf("%d\n", ans);
    }
}
