// =========================================================
// 
//       Filename:  prob104A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/08/2011 11:31:55 AM
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

void solve()
{
    int n; cin >> n;
    int a=10, ans=0;
    for(int b=1; b<=13; ++b)
    {
        int m=4; 
        if (b==1) {
            if (a+1==n || a+11==n) ans+=m;
        }
        else if (b==12) {
            m=3; if (a+10==n) ans+=m;
        }
        else {
            int b2=b;
            if (b>=10) b2=10;
            if (a+b2==n) ans+=m;
        }
    }
    cout << ans << endl;
}
int main()
{
    solve();
}
