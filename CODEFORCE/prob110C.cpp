// =========================================================
// 
//       Filename:  prob110C.cpp
// 
//    Description:  http://codeforces.com/contest/110/problem/C
// 
//        Version:  1.0
//        Created:  09/15/2011 09:43:21 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
using namespace std;


int main()
{
    int n; cin >> n;
    string ans;
    int seven, four;
    for(seven=n/7; seven>=0; seven--)
    {
        if ((n-7*seven)%4 ==0) break;
    }
    four=(n-7*seven)/4;
    if (seven<0) cout << -1 << endl;
    else cout << string(four,'4')+string(seven,'7') << endl;
}
