// =========================================================
// 
//       Filename:  prob111C.cpp
// 
//    Description:  http://codeforces.com/contest/111/problem/C
// 
//        Version:  1.0
//        Created:  09/09/2011 05:59:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/09/2011, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
using namespace std;

#define INF 2500

int dp[50][1<<6][1<<6];

int bitcnt(int k)
{
    int ans=0; while(k) { k&=k-1; ++ans; } return ans;
}

int solve(int n, int m, int prev, int mask)
{
    if (m==0) { if (mask==0) return 0; else return INF; }

    if (dp[m][prev][mask]>=0) return dp[m][prev][mask];

    int best=INF;
    for(int b=0; b<(1<<n); ++b) if ((b&mask)==mask)
    {
        int newmask=0;
        for(int c=0; c<n; ++c)
        {
            if (b&1<<c) continue;
            if (prev&1<<c) continue;
            if (c-1>=0 && (b&1<<(c-1))) continue;
            if (c+1<n && (b&1<<(c+1))) continue;
            newmask|=1<<c;
        }
        int curr = bitcnt(b)+solve(n,m-1,b,newmask);
        best=min(best,curr);
    }
    return dp[m][prev][mask]=best;
}

int main()
{
    int n,m; cin >> n >> m;
    if (n>m) { int t=n; n=m; m=t; }
    memset(dp,-1,sizeof dp);
    int ans = solve(n,m,0,0); // prev, mask
    cout << n*m-ans << endl;
}

// 687365   Sep 10, 2011 5:33:54 AM     lantimilan  C - Petya and Spiders   GNU
// C++  Accepted    30 ms   2200 KB
// 687363   Sep 10, 2011 5:30:30 AM     lantimilan  C - Petya and Spiders   GNU
// C++  Wrong answer on test 52     30 ms   2200 KB
// 687355   Sep 10, 2011 5:11:58 AM     lantimilan  C - Petya and Spiders   GNU
// C++  Wrong answer on test 4  10 ms   2200 KB 
