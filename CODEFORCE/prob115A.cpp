// =========================================================
// 
//       Filename:  prob115A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/15/2011 08:08:14 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int p[2005]; for(int i=0; i<n; ++i) { cin >> p[i]; if (p[i]>=0) p[i]--; }

    int dp[2005]={0};

    int mark[2005]={0};
    int cnt=0;
    while(cnt<n)
    {
        int i;
        for(i=0; i<n; ++i) if (mark[i]==0 && p[i]<0) break;
        mark[i]=1; cnt++;
        for(int k=0; k<n; ++k) if (p[k]==i) {
            dp[k]=max(dp[k],dp[i]+1);
            p[k]=-1;
        }
    }
    int ans=0;
    for(int i=0; i<n; ++i)
    {
        ans=max(ans,dp[i]);
    }
    cout << ans+1 << endl;
}
