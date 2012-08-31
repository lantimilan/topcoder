// =========================================================
// 
//       Filename:  prob108D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/16/2011 11:10:24 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int n,m,h; cin >> n >> m >> h; --h;
    int p,q; p=q=0;
    for(int i=0; i<m; ++i)
    {
        int k; cin >> k;
        q+=k; if (i!=h) p+=k;
    }

    if (q<n) { printf("%.10lf\n", -1.0); return 0; }
    --q; --n;
    double ans=1.0;
    for(int i=0; i<n; ++i, --p,--q)
        ans*=1.0*p/q;
    ans=1.0-ans;
    printf("%.10lf\n", ans);
}
