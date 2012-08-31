// =========================================================
// 
//       Filename:  prob137B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/15/2011 10:12:26 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/15/2011, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int a[5005]={0};
    int n; scanf("%d", &n);
    for(int i=0; i<n; ++i)
    {
        int d; scanf("%d", &d);
        a[d]=1;
    }

    int ans=n;
    for(int i=1; i<=n; ++i)
        ans -= a[i];
    printf("%d\n", ans);
}
