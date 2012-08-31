// =========================================================
// 
//       Filename:  prob118D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/07/2011 09:36:18 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/07/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

const int MOD=100000000;

int main()
{
    int n1,n2,k1,k2; 
    scanf("%d%d%d%d\n",&n1,&n2,&k1,&k2);

    int dp[105][15][105][15]; // n1,k1,n2,k2
    memset(dp,0,sizeof dp);

    dp[0][0][0][0]=1;

    for(int i=0; i<=n1; ++i)
    for(int j=0; j<=n2; ++j)
    for(int l=0; l<=k1; ++l)
    for(int p=0; p<=k2; ++p)
    {
        if (i+1<=n1 && l+1<=k1) { // footman
            dp[i+1][l+1][j][0]+=dp[i][l][j][p];
            dp[i+1][l+1][j][0]%=MOD;
        }
        if (j+1<=n2 && p+1<=k2) { // horseman
            dp[i][0][j+1][p+1]+=dp[i][l][j][p];
            dp[i][0][j+1][p+1]%=MOD;
        }
    }
    int ans=0;
    for(int l=0; l<=k1; ++l)
    for(int p=0; p<=k2; ++p)
    {
        ans+=dp[n1][l][n2][p];
        ans%=MOD;
    }
    printf("%d\n",ans);
}

// 749785   Oct 8, 2011 8:44:24 AM  lantimilan  D - Caesars Legions     GNU C++
// Accepted     50 ms   11000 KB 
