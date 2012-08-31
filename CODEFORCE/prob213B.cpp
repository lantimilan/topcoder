// =========================================================
// 
//       Filename:  prob213B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/31/2012 10:12:40 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/31/2012, LI YAN
// 
// =========================================================

typedef long long int64;

const int MOD=1000000000+7;

int A[15];
int dp[110];
int fact[110];
int comb[110][110];

int add(int a, int b)
{
    return ((int64)a+b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a * b % MOD;
}

int fastpow(int a, int n)
{
    int b=a;
    int ans=1;
    while(n) {
        if (n&1) ans = mult(ans, b);
        n/=2;
        b = mult(b, b);
    }
    return ans;
}

int inv(int a)
{
    return fastpow(a, MOD-2);
}

void init()
{
    fact[0]=1;
    for(int i=1; i<=100; ++i)
        fact[i] = mult(fact[i-1], i);
    
    for(int n=0; n<=100; ++n)
    for(int r=0; r<=n; ++r)
        comb[n][r] = fact[n] * inv(fact[r]);
}

int getcomb(int n, int r)
{
    if (n<r) return 0;
    return comb[n][r];
}

int main()
{
    int n; scanf("%d", &n);
    for(int i=0; i<10; ++i) scanf("%d", A+i);

    int l=0;
    for(int i=1; i<10; ++i) l+=A[i];
    dp[l]=fact[l];
    for(int i=1; i<10; ++i)
        dp[l] = mult(dp[l], inv(fact[A[i]]));
    
    int ans=0;
    if (A[0] <= n-l) ans = mult(dp[l], getcomb(n-1, n-l));
    for(++l; l<=n; ++l) {
        dp[l] = mult(dp[l-1], 9);
        if (A[0] <= n-l)
            ans = add(ans, mult(dp[l], getcomb(n-1, n-l)));
    }

    printf("%d\n", ans);
}
