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
// for n odd, it must be n,(n-1),(n-2)
// for n even, one option is to use (n-1), (n-2), (n-3)
// the only other options that have to beat the above are
// the first one has to be n, or it will be dominated by the above
// the second one is then either n-1 or n-2, using n-3 would result in
// n, n-3, n-4 and the product is already too small
// n, n-1, n-a for some a such that n(n-1)(n-a) >= (n-1)(n-2)(n-3),
// then a cannot be too small
// same thing n, n-2, n-b, and b cannot be too small
//
