// =========================================================
// 
//       Filename:  prob106C.cpp
// 
//    Description:  http://codeforces.com/contest/106/problem/C
// 
//        Version:  1.0
//        Created:  09/13/2011 08:55:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/13/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <map>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

int M;
vector<int> A,B,C,D;

map<pii,int> dp;

int solve(int dough, int type)
{
    if (type>M) return 0;
    pii conf(dough,type);
    if (dp.count(conf)) return dp[conf];

    int &ans=dp[conf]; ans=0;
    int cap=dough/C[type];
    if (type>0) cap=min(cap, A[type]/B[type]);
    for(int i=0; i<=cap; ++i)
    {
        int curr=D[type]*i + solve(dough-C[type]*i,type+1);
        ans=max(ans,curr);
    }
    return ans;
}

int main()
{
    int n,m; scanf("%d%d",&n,&m); M=m;
    vector<int> c(m+1);
    vector<int> d(m+1);
    vector<int> a(m+1); a[0]=n;
    vector<int> b(m+1); b[0]=0;
    scanf("%d",&c[0]);
    scanf("%d",&d[0]);
    for(int i=1; i<=m; ++i)
        scanf("%d%d%d%d",&a[i],&b[i],&c[i],&d[i]);
    A=a; B=b; C=c; D=d;
    int ans = solve(n,0);
    printf("%d\n",ans);
}
