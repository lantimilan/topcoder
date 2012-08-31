// =========================================================
// 
//       Filename:  prob140A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/04/2012 07:13:28 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/04/2012, LI YAN
// 
// =========================================================
#include <cmath>
#include <cstdio>
using namespace std;

int main()
{
    int n, R, r; 
    scanf("%d%d%d", &n, &R, &r);
    bool ans=true;
    if (n==1) ans = (R>=r);
    else if (n==2) ans = (R>=2*r);
    else {
        double rr = r*(1+1.0/sin(acos(-1.0)/n));
        ans = (R>=rr-1.0e-9);
    }
    if (ans) puts("YES");
    else puts("NO");
}
