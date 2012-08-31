// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/22/2011 08:03:42 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/22/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

#define sz(a) int(a.size())

void solve()
{
    string s; cin >> s;
    char last;
    int i;
    for(i=0; i<sz(s)&&s[i]!='.'; ++i);
    last=s[i-1];
    string ans = s.substr(0,i);
    if (last!='9') {
        if (s[i+1]<='4') { cout << ans << endl; return; }
        else {
            ans[sz(ans)-1]++;
            cout << ans << endl; return;
        }
    }
    else cout << "GOTO Vasilisa." << endl;
}
int main()
{
    solve();
}
