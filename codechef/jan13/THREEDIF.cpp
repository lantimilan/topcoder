// =========================================================
// 
//       Filename:  THREEDIF.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/05/2013 09:37:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/05/2013, LI YAN
// 
// =========================================================

// sort n1, n2, n3
// then there are n1 ways to choose the first one, 
// n2 - 1 ways to choose the second one, since one of them is taken
// n3 - 2 ways to choose the third one

#include <algorithm>
#include <iostream>
using namespace std;

const int M = 1e9+7;

int main()
{
    int T; cin >> T;
    while (T--) {
        long long a[3];
        for (int i=0; i<3; ++i) {
            cin >> a[i];
        }
        sort(a, a+3);
        a[1]--; a[2]-=2;
        for (int i=0; i<3; ++i) {
            a[i] %= M;
        }
        long long ans = 1;
        for (int i=0; i<3; ++i) {
            ans = (ans * a[i]) % M;
        }
        cout << ans << endl;
    }
}

// 
// Correct Answer
// Execution Time: 0.00 
