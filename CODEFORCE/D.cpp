// =========================================================
// 
//       Filename:  D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/22/2011 08:49:38 AM
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

typedef long long LL;

LL gcd(LL a, LL b)
{
    if (b==0) return a;
    return gcd(b,a%b);
}

int main()
{
    LL n; cin >> n;
    LL k=0;
    while((1LL<<k) < n) ++k;

    //LL a=k*(1LL<<k), b=n;
    LL a=1LL<<k, b=n;
    LL g = gcd(a,b); a/=g; b/=g;
    g=gcd(k,b); k/=g; b/=g; a*=k;
    cout << a << '/' << b << endl;
}
