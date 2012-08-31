// =========================================================
// 
//       Filename:  prob104B.cpp
// 
//    Description:  http://codeforces.com/contest/104/problem/B
// 
//        Version:  1.0
//        Created:  08/08/2011 11:37:52 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/08/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long LL;

void solve()
{
    LL ans=0;   
    int n; cin >> n;
    for(int i=1; i<=n; ++i)
    {
        LL k; cin >> k;
        ans += k*i - (i-1);
    }
    cout << ans << endl;
}
int main()
{
    solve();
}
