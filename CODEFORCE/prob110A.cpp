// =========================================================
// 
//       Filename:  prob110A.cpp
// 
//    Description:  http://codeforces.com/contest/110/problem/A
// 
//        Version:  1.0
//        Created:  09/15/2011 09:32:15 PM
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
    long long n; cin >> n;
    int d=0;
    while(n) {
        if (n%10==4 || n%10==7) d++;
        n/=10;
    }
    bool lucky=false;
    while(d) {
        if (d%10==4 || d%10==7) { lucky=true; }
        else { lucky=false; break; }
        d/=10;
    }
    if (lucky) cout << "YES" << endl;
    else cout << "NO" << endl;
}
