// =========================================================
// 
//       Filename:  PPERM.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2012 10:28:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

const int MOD = 1000000000+7;
int P;
bool isprime[5000000+5];
int primes[5000000+5];
int cnt[5000000+5];
int res[5000000+5];

void init() {
    int n = 5000000+5;
    for(int i=2; i<n; ++i) isprime[i] = true;
    for(int i=2; i<n; ++i) if (isprime[i]) {
        primes[P++] = i;
        for(int j=i+i; j<n; j+=i) {
            isprime[j] = false;
        }
    }
    int x = 0;
    for(int i=2; i<n; ++i) {
        cnt[i] = cnt[i-1];
        if (x < P && primes[x] == i) {
            cnt[i]++; x++;
        }
    }
}

int mult(int a, int b) {
    return (long long)a*b % MOD;
}
void pre() {
    int n = 5000000;
    res[1] = 1;
    for(int i=2; i<=n; ++i) {
        res[i] = mult(res[i-1], cnt[i]+1);
    }
}

int main()
{
    int T; scanf("%d", &T);
    init();
    pre();
    while (T--) {
        int N; scanf("%d", &N);
        printf("%d\n", res[N]);
    }
}

// algorithm:
// after placing 1 to N-1, you can put N in pos=1,2,3,5,... (prime pos)
// so f[n] = f[n-1] * (1+cnt[n]) where cnt[n] is number of primes <= n
//
// Why WA? because I forgot to set cnt[5000000]
//
