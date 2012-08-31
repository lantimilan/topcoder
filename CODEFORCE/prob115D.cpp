// =========================================================
// 
//       Filename:  prob115D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/15/2011 08:54:55 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
using namespace std;

#define sz(a) int(a.size())

const int MOD=1000000+3;
int dp[2005][2005];

bool isop(char ch)
{
    return ch=='+'||ch=='-'||ch=='*'||ch=='/';
}
int calc(int a, int b, const string &expr)
{
//cout << a << ' ' << b << endl;
    if (a>=b) return 0;
    int &ans=dp[a][b]; if (ans>=0) return ans;

    if (expr[a]=='*' || expr[a]=='/') return 0;

    if (expr[a]=='+' || expr[a]=='-') {
        ans = calc(a+1,b,expr);
        for(int i=a+1; i<b; ++i) if (isop(expr[i]))
            ans = (ans + (long long)calc(a+1,i,expr)*calc(i+1,b,expr)%MOD)%MOD;
        return ans;
    }
    string ops="+-*/";
    bool hasop=false;
    for(int i=a; i<b; ++i)
    {
        if (isop(expr[i])) { hasop=true; break; }
    }
    if (!hasop) return 1;

    ans=0;
    for(int i=a; i<b; ++i)
    {
        char ch=expr[i];
        int p; for(p=0; p<sz(ops)&&ch!=ops[p]; ++p);
        if (p<sz(ops)) {
            int t1=calc(a,i,expr);
            int t2=calc(i+1,b,expr);
            ans = (ans + (long long)t1*t2%MOD)%MOD;
        }
    }
    //cout << a << ' ' << b << ' ' << ans << endl;
    return ans;
}

int main()
{
    string expr; cin >> expr;
    memset(dp,-1,sizeof dp);
    int ans=calc(0,sz(expr),expr);
    cout << ans << endl;
}

// hacked, TLE
// 1+1+1+1+...+1
// 26s on local machine
//
