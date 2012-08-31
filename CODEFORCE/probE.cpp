// =========================================================
// 
//       Filename:  probE.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/23/2011 09:14:10 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/23/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    double total, covered;
    int x[512][4], y[512][4];
    for(int i=0; i<n; ++i)
    for(int j=0; j<4; ++j) cin >> x[i][j] >> y[i][j];

    // calc area not covered by any rect
}
