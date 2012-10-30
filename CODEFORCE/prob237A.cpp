// =========================================================
// 
//       Filename:  prob237A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/25/2012 08:32:56 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/25/2012, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int hh, mm;
    int maxcnt, cnt;
    hh = mm = -1;
    maxcnt = cnt = 0;
    for(int i=0; i<n; ++i) {
        int h, m;
        cin >> h >> m;
        if (h==hh && m == mm) cnt++;
        else { 
            hh = h; mm = m;
            maxcnt = max(maxcnt, cnt);
            cnt = 1;
        }
    }
    maxcnt = max(maxcnt, cnt);
    cout << maxcnt << endl;
}
