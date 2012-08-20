// =========================================================
// 
//       Filename:  LUKYDRIV.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/LUKYDRIV
// 
//        Version:  1.0
//        Created:  08/01/2012 09:15:17 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;
const int MOD = 1000000000+7;
int dp[10000+5][12][5]; // pos, rem, len
char line[10000+5];

int refadd(int &a, int b)
{
    return a = ((int64)a+b) % MOD;
}

int main()
{
    int T; scanf("%d ", &T);
    while(T--) {
        memset(dp[0], 0, sizeof dp[0]);
        scanf("%s", line); 
        int n = strlen(line);
        dp[0][0][0]=1;
        for(int p=0; p<n; ++p)
        {
        int d = line[p]-'0';
        memcpy(dp[p+1], dp[p], sizeof dp[p+1]);
        for(int r=0; r<10; ++r) 
        for(int l=0; l<4; ++l)
        {
            // use line[p]
            //if (l+1<=4) {
                int t = r+d;
                if (t>9) t-=9;

                //if (t==0) refadd(dp[p+1][0][l+1], dp[p][0][l]);
                //else if (t==9) refadd(dp[p+1][9][l+1], dp[p][r][l]);
                //else refadd(dp[p+1][t][l+1], dp[p][r][l]);
                int &next = dp[p+1][t][l+1];
                next = ((int64)next + dp[p][r][l]) % MOD;
            //}
            // not use line[p]
            //dp[p+1][r][l] = refadd(dp[p+1][r][l], dp[p][r][l]);
        }
        }
        int ans=0;
        for(int l=1; l<=4; ++l) refadd(ans, dp[n][9][l]);
        printf("%d\n", ans);
    }
}

