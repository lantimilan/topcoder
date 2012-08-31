// =========================================================
// 
//       Filename:  prob104D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  08/07/2011 04:30:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/07/2011, LI YAN
// 
// =========================================================

#include <iostream>
using namespace std;

typedef long long LL;

char query(LL n, LL k, LL x)
{
    LL l = n-k;
    if (k>=n-k) {
        if (x<=2*l) { if (x%2==0) return 'X'; else return '.'; }
        else return 'X';
    }
    else {
        if ((n-2*k)%2==0) {
            if (x<=n-2*k) return '.';
            else return (x-(n-2*k))%2==0 ? 'X' : '.';
        }
        else {
            if (x<=n-2*k+1) return '.';
            if (x==n) return 'X';
            return (x-(n-2*k+1))%2==0 ? 'X' : '.';
        }
    }
}

void solve()
{
    LL n, k; int p; cin >> n >> k >> p;
    LL x;
    for(int i=0; i < p; ++i)
    {
        cin >> x;
        cout << query(n,k,x);
    }
    cout << endl;
}
int main()
{
    solve();
}
