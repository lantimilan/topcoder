// =========================================================
// 
//       Filename:  prob111A.cpp
// 
//    Description:  http://codeforces.ru/contest/111/problem/A
// 
//        Version:  1.0
//        Created:  09/07/2011 04:57:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/07/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long LL;

int main()
{
    int n; LL x; int y; cin >> n >> x >> y;
    LL last = y-(n-1); if (last <= 0) { cout << -1 << endl; return 0; }
    if (n-1+last*last < x) { cout << -1 << endl; return 0; }
    for(int i=0; i<n-1; ++i)
    {
        cout << 1 << ' ';
    }
    cout << last << endl;
}
