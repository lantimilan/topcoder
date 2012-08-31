// =========================================================
// 
//       Filename:  prob110B.cpp
// 
//    Description:  http://codeforces.com/contest/110/problem/B
// 
//        Version:  1.0
//        Created:  09/15/2011 09:39:41 PM
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
    string s="abcd";
    string ans;
    for(int i=0; i<n; )
    {
        for(int j=0; j<4 && i<n; ++j, ++i)
            ans+=s[j];
    }
    cout << ans << endl;
}
