// =========================================================
// 
//       Filename:  prob219B.cpp
// 
//    Description:  http://codeforces.com/contest/219/problem/B
// 
//        Version:  1.0
//        Created:  08/30/2012 07:56:32 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/30/2012, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long int64;

int main()
{
    int64 p, d;
    cin >> p >> d;
    int64 ans = (int64)1e18 - 1; //cout << ans << endl;
    while(ans > p) ans /= 10; //cout << ans << endl;
    for(; ; ans /= 10) {
        int64 factor = ans+1;
        int64 tmp;
        tmp = p/factor*factor + ans;
        if (tmp > p) {
            tmp = (p/factor-1)*factor + ans;
        }
        if (p - tmp <= d) {
            ans = tmp; break;
        }
        if (ans==0) {
            ans = tmp; break;
        }
    }
    cout << ans << endl;
}
