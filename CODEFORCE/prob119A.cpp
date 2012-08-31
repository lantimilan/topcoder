// =========================================================
// 
//       Filename:  prob119A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/14/2011 10:11:36 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/14/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

int gcd(int a, int b)
{
    if (b==0) return a;
    if (a<b) return gcd(b,a);
    return gcd(b,a%b);
}

int main()
{
    int a,b,n; cin >> a >> b >> n;

    int turn=0;
    while(n) {
        int g;
        if (turn==0) { g=gcd(a,n); }
        else { g=gcd(b,n); }
        n-=g; turn=1-turn;
    }
    cout << 1-turn << endl;
}
