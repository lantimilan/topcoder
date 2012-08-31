// =========================================================
// 
//       Filename:  prob116A.cpp
// 
//    Description:  http://codeforces.com/contest/116/problem/A
// 
//        Version:  1.0
//        Created:  09/15/2011 01:27:21 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    int cap=0, vol=0;
    for(int i=0; i<n; ++i)
    {
        int a,b; cin >> a >> b; // exit, enter
        vol+=b-a;
        cap=max(cap,vol);
    }
    cout << cap << endl;
}
