// =========================================================
// 
//       Filename:  prob236C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/21/2012 06:25:38 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/21/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
using namespace std;

long long gcd(long long a, long long b)
{
    if (b==0) return a;
    else return gcd(b, a%b);
}

int main()
{
    int n; cin >> n;
    long long a, b, c;
    long long ans;
    if (n&1) {
        a = n; b = max(1LL, a-1); c = max(1LL, b-1);
        ans = a*b*c;
    } else {
        ans = 1;
        a = n; b = max(1, n-1);
        for(c=max(1LL, b-1); c>=1; --c) {
            ans = max(ans, a*b*c/gcd(a*b, c));
        }
        a = n-1; b = max(1LL, a-1); c = max(1LL, b-1);
        ans = max(ans, a*b*c);
    }
    cout << ans << endl;
}

// Accepted
// but how do you prove it?
//
