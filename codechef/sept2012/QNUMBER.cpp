// =========================================================
// 
//       Filename:  QNUMBER.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/QNUMBER
// 
//        Version:  1.0
//        Created:  09/02/2012 03:25:23 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/02/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
using namespace std;

typedef long long int64;

const int MAX = 1000000;

int64 divisors[2*MAX+10];
int factors[2*MAX+10];
int primes[MAX+10];
bool isprime[MAX+10];
int P, D;

map<int64, int> mp;

void init(int64 N)
{
    // 3.934 s
    /*
    for(int i=1; i<=1000000; ++i) {
        for(int j=1; j*j <= i; ++j) {
            if (i%j == 0) factor[i]+=2;
            if (i==j*j) factor[i]--;
        }
    }
    */
    // get N's factors
    D=0;
    for(int i=1; i <= N/i; ++i) if (N%i==0) {
        divisors[D++] = i;
        if (i != N/i) divisors[D++] = N/i;
    }
    sort(divisors, divisors+D);
    for(int i=0; i<D; ++i) mp[divisors[i]] = i;
    P=0;
    for(int i=0; i<MAX; ++i)
        isprime[i] = true;
    isprime[0] = isprime[1] = false;
    for(int i=2; i<MAX; ++i) if (isprime[i]) {
        primes[P++] = i;
        for(int j=i+i; j<MAX; j+=i)
            isprime[j] = false;
    }
    for(int i=0; i<D; ++i) {
        int res = 1;
        int64 val = divisors[i];
        for(int x=0; x < P && primes[x] <= val/primes[x]; x++) {
            if (val % primes[x] == 0) {
                int cnt = 0;
                while(val % primes[x] == 0) {
                    cnt++; val /= primes[x];
                }
                res *= (cnt+1);
            }
        }
        if (val>1) res *= 2;
        factors[i] = res;
    }
    /*
    for(int i=1; i<=20; ++i) {
        printf("%d: %d\n", i, factors[i]);
    }
    */
}

int64 gcd(int64 a, int64 b)
{
    if (b==0) return a;
    return gcd(b, a%b);
}

int main()
{
    int64 N, Q; scanf("%lld%lld", &N, &Q);
    init(N);
    for(int i=0; i<Q; ++i) {
        int64 T, K; scanf("%lld%lld", &T, &K);
        int ans;
        int64 g;
        switch(T) {
            case 1:
                g = gcd(N, K);
                ans = factors[mp[g]];
                break;
            case 2: // factors of N that is divisible by K
                if (N%K != 0) ans = 0;
                else {
                    ans = factors[mp[N/K]];
                }
                break;
            case 3: // factors of N that is not divisible by K
                if (N%K != 0) ans = factors[mp[N]];
                else {
                    ans = factors[mp[N]] - factors[mp[N/K]];
                }
                break;
            default:
                assert(false);
                break;
        }
        printf("%d\n", ans);
    }
}

// 1305857 4 min ago  AC      43.17   30.5M   C++ 4.3.2   
// 1305835 14 min ago RE   39.54   30.5M   C++ 4.3.2   
// 1305793 36 min ago RE   39.12   30.5M   C++ 4.3.2   
// 1305718 1 hours ago WA    0.19    30.4M   C++ 4.3.2   
// 1305651 1 hours ago     0.18    19M C++ 4.3.2   
