// =========================================================
// 
//       Filename:  prob156C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  03/01/2012 09:28:59 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/01/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int64;
const int MOD=1000000000+7;
int dp[105][30];
int sum[105][30]; // prefix sum
char s[105];

void refadd(int &a, int b)
{
    a=((int64)a+b)%MOD;
}

int sub(int a, int b)
{
    return (a-b+MOD)%MOD;
}

int main()
{
    int T; scanf("%d ", &T);
    for(int t=0; t<T; ++t) {
        memset(dp, 0, sizeof dp);
        memset(sum, 0, sizeof sum);
        gets(s);
        int n=strlen(s);
        dp[0][s[0]-'a'+1]=1;
        for(int i=s[0]-'a'+1; i<=26; ++i) sum[0][i]=1;
        for(int pos=1; pos<n; ++pos) {
            for(char ch='a'; ch<='z'; ++ch) {
                int diff = s[pos]-ch;
                if (diff >=0) refadd(dp[pos][ch-'a'+1], sum[pos-1][26-diff]);
                else refadd(dp[pos][ch-'a'+1], sub(sum[pos-1][26], sum[pos-1][-diff]));
            }
            for(int i=1; i<=26; ++i) { 
                sum[pos][i] = sum[pos][i-1];
                refadd(sum[pos][i], dp[pos][i]);
            }
        }
        printf("%d\n", sub(sum[n-1][26],1));
    }
}
