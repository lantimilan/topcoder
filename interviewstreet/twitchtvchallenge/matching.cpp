// =========================================================
// 
//       Filename:  matching.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/05/2012 03:19:38 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/05/2012, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long int64;

const int MOD = 1000000000+7;

int mult(int a, int b)
{
    return (int64)a*b %MOD;
}

int fastpow(int a, int n)
{
    int ans=1;
    while(n) {
        if (n&1) ans = mult(ans, a);
        a = mult(a, a);
        n/=2;
    }
    return ans;
}

int inv(int n)
{
    return fastpow(n, MOD-2);
}

int main()
{
    int n; cin >> n;
    int ans=1;
    int x=1;
    for(int i=2; i<=2*n; ++i) {
        x = mult(x,i);
        if (i==n) ans = mult(ans, inv(x));
        if (i==n+1) ans = mult(ans, inv(x));
    }
    ans = mult(ans, x);
    cout << ans << endl;
}

// Matching     cpp     2012-05-06 03:55:10     Processed   Accepted
// Score: 100
//  View Details
