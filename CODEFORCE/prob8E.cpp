// =========================================================
// 
//       Filename:  prob8E.cpp
// 
//    Description:  http://codeforces.com/contest/8/problem/E
// 
//        Version:  1.0
//        Created:  09/29/2011 11:28:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/29/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
using namespace std;

long long calc(int n, int p, const string &prefix)
{
    long long ans=1LL<<(n-p);
    long long pal;
    if (n>=2*p) pal=1LL<<(n-2*p+1);
    else {
        int ispal=1, isflip=1;
        for(int i=int(prefix.size())-1; i>=n/2; --i) {
            if (prefix[i]!=prefix[n-1-i]) { ispal=0; }
            if (prefix[i]==prefix[n-1-i]) { isflip=0; }
        }
        pal=ispal+isflip;
    }
    return (ans-2*pal)/2+pal;
}
int main()
{
    int n;
    long long k;
    cin >> n >> k;

    --k;
    bool hasone=false;
    string ans="0";
    for(int p=1; p<n; ++p) {
        long long cnt = calc(n,p,ans);
        if (!hasone) --cnt; cout << cnt << ' ' << k << endl;
        if (k>=cnt) { k-=cnt; ans+='1'; hasone=true; }
        else ans+='0';
    }
    if (k>0) cout << -1 << endl;
    else cout << ans << endl;
}
