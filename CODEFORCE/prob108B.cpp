// =========================================================
// 
//       Filename:  prob108B.cpp
// 
//    Description:  http://codeforces.com/contest/108/problem/B
// 
//        Version:  1.0
//        Created:  09/16/2011 10:10:48 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n; cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; ++i)
        cin >> a[i];
    sort(a.begin(), a.end());
    bool good=true;
    for(int i=1; i<n; ++i)
    {
        if (a[i]==a[i-1] || a[i]>=a[i-1]*2) {}
        else { good=false; break; }
    }

    if (good) cout << "NO" << endl;
    else cout << "YES" << endl;
}

