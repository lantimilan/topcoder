// =========================================================
// 
//       Filename:  prob186A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/04/2012 08:31:43 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/04/2012, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    bool ans=true;
    if (s1.length() != s2.length()) ans=false;
    int cnt=0;
    char c1[2], c2[2];
    for(int i=0; i<s1.length(); i++) {
        if (s1[i] != s2[i]) {
            c1[cnt]=s1[i]; c2[cnt]=s2[i];
            cnt++; if (cnt>2) { ans=false; break; }
        }
    }
    if (c1[0]!=c2[1] || c1[1]!=c2[0]) ans=false;
    if (ans) cout << "YES" << endl;
    else cout << "NO" << endl;
}
