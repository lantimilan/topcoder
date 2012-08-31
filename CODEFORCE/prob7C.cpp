// =========================================================
// 
//       Filename:  prob7C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/19/2011 09:22:59 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/19/2011, LI YAN
// 
// =========================================================

// extended euclidean

#include <iostream>
#include <utility>

using namespace std;

typedef long long LL;
typedef pair<LL,LL> PLL;

LL gcd(LL a, LL b)
{
    if (a%b==0) return b;
    return gcd(b,a%b);
}

PLL egcd(LL a, LL b)
{
    if (b==0LL) return PLL(1LL,0LL);
    PLL prev = egcd(b,a%b);
    LL x = prev.first, y = prev.second;
    return PLL(y,x-a/b*y);
}

int main()
{
    LL A, B, C; cin >> A >> B >> C;

    if (A==0) {
        if (C%B==0) cout << 0 << ' ' << -C/B << endl;
        else cout << -1 << endl;
        return 0;
    }
    else if (B==0) {
        if (C%A==0) cout << -C/A << ' ' << 0 << endl;
        else cout << -1 << endl;
        return 0;
    }
    LL pA = A>=0 ? A : -A;
    LL pB = B>=0 ? B : -B;
    LL g = gcd(pA,pB);
    if (C%g!=0) { cout << -1 << endl; return 0; }

    PLL p = egcd(pA,pB);
    LL x = (A>=0)?p.first:-p.first;
    LL y = (B>=0)?p.second:-p.second;
    LL t = -C/g;
    cout << x*t << ' ' << y*t << endl;
}
