// =========================================================
//
//       Filename:  test.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  01/06/2012 08:39:06 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/06/2012, LI YAN
//
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    int cnt = 0;
    int a[6];
    int n = 6;
    int nrow = 2, ncol = n / nrow;
    for (int i=0; i<9; ++i) a[i] = i+1;
    do {
        bool good = true;
        for (int i=0; i<nrow; ++i)
        for (int j=0; j<ncol; ++j) {
            int next = ncol*i+j+1;
            if (next < n && next % ncol > j && a[ncol*i+j] > a[next]) { good = false; }
            next = ncol*(i+1)+j;
            if (next < n && next / ncol > i && a[ncol*i+j] > a[next]) { good = false; }
        }
        if (good) {
            for (int i=0; i<n; ++i) { cout << a[i] << ' '; if ((i+1) % ncol == 0) cout << endl; }
            cout << endl;
            cnt++;
        }
    } while (next_permutation(a, a+n));
    cout << "cnt " << cnt << endl;
}
