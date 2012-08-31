// =========================================================
// 
//       Filename:  prob106E.cpp
// 
//    Description:  E. Space Rescuers
//    http://codeforces.com/contest/106/problem/E
// 
//        Version:  1.0
//        Created:  08/19/2011 12:29:26 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/19/2011, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int main()
{
    int n; cin >> n;
    double pts[200][3];
    double ans[3];
    int k[4];

    for(int i=0; i<n; ++i)
        for(int j=0; j<3; ++j)
        scanf("%lf", &pts[i][j]);

    if (n<=1) {
        for(int j=0; j<3; ++j) ans[j]=pts[0][j];
    } else if (n==2) {
        for(int j=0; j<3; ++j) ans[j]=(pts[0][j]+pts[1][j])/2;
    }
}
