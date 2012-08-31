// =========================================================
// 
//       Filename:  prob149D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/12/2012 11:52:03 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/12/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=705;
const int MOD=1000000000+7;
char s[MAXN];
int match[MAXN];
int dp[MAXN][MAXN][5][5];

void refadd(int &a, int b)
{
    a=((long long)a+b)%MOD;
}

int mult(int a, int b)
{
    return (long long)a*b %MOD;
}

// begin-1 is c1, end is c2
//
int calc(int begin, int end, int c1, int c2)
{
    if (begin >= end) return 1;
    int &ans = dp[begin][end][c1][c2];
    if (ans>=0) return ans;

    ans=0;
    int k = match[begin];
    int t1=0, t2=0;
    int x1,x2;

    if (k==end-1) { // (...)
        for(x1=0; x1<3; ++x1) if (c1==0 || c1!=x1)
        for(x2=0; x2<3; ++x2) if ((c2==0 || c2!=x2) && (x1*x2==0) && (x1+x2>0))
            refadd(ans, calc(begin+1, end-1, x1, x2));
    }
    else { // (...)( )
        for(x1=0; x1<3; ++x1) if (c1==0 || c1!=x1)
        for(x2=0; x2<3; ++x2) if ((x1*x2==0) && (x1+x2>0))
        {
            t1=calc(begin+1, k, x1, x2); 
            t2=calc(k+1, end, x2, c2);
            refadd(ans, mult(t1, t2));
        }
    }
    return ans;
}

int main()
{
    gets(s);
    int n = strlen(s);
    int ans=0;

    vector<int> v;
    for(int i=0; i<n; ++i) {
        if (s[i]=='(') v.push_back(i);
        else {
            int j=v.back();
            match[i]=j; match[j]=i;
            v.pop_back();
        }
    }
    memset(dp, -1, sizeof dp);
    ans = calc(0,n,0,0);
    printf("%d\n", ans);
}

// 1174774  Feb 13, 2012 1:15:15 AM     lantimilan  D - Coloring Brackets   GNU
// C++  Accepted    50 ms   50000 KB 
