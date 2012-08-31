// =========================================================
// 
//       Filename:  prob1A.cpp
// 
//    Description:  Problem:      1A - Theater Square 
// 
//        Version:  1.0
//        Created:  03/13/2011 10:10:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/13/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long LL;

int main()
{
    LL n, m, a; 
    while(cin >> n >> m >> a) {
    //cout << n << " " << m << " " << a << endl;
    LL res = ((m+a-1)/a) * ((n+a-1)/a);
    cout << res << endl;
    }
}
