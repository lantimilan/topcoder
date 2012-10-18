// =========================================================
// 
//       Filename:  scoreboard.cpp
// 
//    Description:  Count Scorecards(30 points)
// 
//        Version:  1.0
//        Created:  10/17/2012 07:39:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/17/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

const int MOD = 1e9+7;
int N;
int s[50];
int dp[50][800][50];

void solve()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%d", s+i);

    memset(dp, 0, sizeof dp);
    dp[0][0][0]=1;
    for(int n=1; n<=N; ++n) {
        for(int sum=n*(n-1)/2; sum <= n*N/2; ++sum) {
        int low, upp;
        if (s[n-1] >= 0) { low = upp = s[n-1]; }
        else { low = n/2; upp = N-1; }
        for(int last=low; last <= upp; ++last) {
            for(int prev=(n-1)/2; prev <= last; ++prev) {
                if (sum >= last)
                    dp[n][sum][last] += dp[n-1][sum-last][prev];
            }
            //printf("dp[%d][%d][%d] %d\n", n, sum, last, dp[n][sum][last]);
        }
        }
    }
    int ans = 0;
    int sum = N*(N-1)/2;
    for(int last=0; last<N; ++last)
        ans += dp[N][sum][last];
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}

// last case
// 0 1 2 3, there are 3*3 = 9 choices since each of the three -1 can be 0, 1, 3
// 1 1 2 2, there are 3 choice since one of the three -1 has to be 2
