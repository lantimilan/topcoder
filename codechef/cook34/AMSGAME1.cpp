// =========================================================
// 
//       Filename:  AMSGAME1.cpp
// 
//    Description:  gcd
// 
//        Version:  1.0
//        Created:  05/19/2013 09:08:38 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/19/2013, LI YAN
// 
// =========================================================

#include <iostream>
#include <set>
using namespace std;

int a[1005];

int gcd(int x, int y)
{
    return y == 0 ? x : gcd(y, x % y);
}

void solve()
{
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {  cin >> a[i]; }

    int g = a[0];
    for (int i = 1; i < N; ++i) {
        g = gcd(g, a[i]);
    }
    cout << g << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
