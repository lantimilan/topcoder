// =========================================================
// 
//       Filename:  jewels.cpp
// 
//    Description:  Jewels and Stones
// 
//        Version:  1.0
//        Created:  05/03/2012 04:03:22 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void solve()
{
    string s1, s2; cin >> s1 >> s2;
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    int ans=0;
    for(int i=0, j=0; i<s1.length() && j<s2.length(); ) {
        if (s2[j]==s1[i]) { ++ans; ++j; }
        else if (s2[j] < s1[i]) { ++j; }
        else { ++i; }
    }
    cout << ans << endl;
}
int main()
{
    int T; cin >> T;
    for(int t=1; t<=T; ++t) solve();
}
