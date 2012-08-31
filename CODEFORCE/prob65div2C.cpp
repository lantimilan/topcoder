// =========================================================
// 
//       Filename:  prob65div2C.cpp
// 
//    Description:  C. Round Table Knights
// 
//        Version:  1.0
//        Created:  03/29/2011 04:01:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/29/2011, LI YAN
// 
// =========================================================

#include <cmath>
#include <iostream>
using namespace std;

void solve()
{
    int n; cin >> n;
    int knights[100000+10];
    for(int i=0; i<n; ++i) cin >> knights[i];

    for(int d=1; d <= int(sqrt(n)); ++d) if (n%d==0)
    {
        int deno = d;
        for(int k=0; k < 2; ++k)
        {
            deno = n/deno;
            if (deno <3) continue;
            for(int s=0; s<n/deno; ++s)
            { 
                bool good = true;
                for(int k=s; k<n; k+=n/deno)
                    if (!knights[k]) { good=false; break; }
                if (good) { cout << "YES\n"; return; }
            }
        }

    }
    cout << "NO\n";
}
int main()
{
    solve();
}
