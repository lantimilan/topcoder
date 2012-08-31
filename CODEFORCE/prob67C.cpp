// =========================================================
// 
//       Filename:  prob67C.cpp
// 
//    Description:  C. Modified GCD
// 
//        Version:  1.0
//        Created:  04/13/2011 08:41:59 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/13/2011, LI YAN
// 
// =========================================================

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
    if (a%b == 0) return b;
    else return gcd(b,a%b);
}

void solve()
{
    int a,b; cin >> a >> b;
    int g = gcd(a,b);
    vector<int> v1, v2, all;
    for(int k=1; k<=int(sqrt(g)); ++k)
    { if (g%k==0) { v1.push_back(k); v2.push_back(g/k); } }

    for(int i=0; i<int(v1.size()); ++i) all.push_back(v1[i]);
    for(int i=int(v2.size())-1; i>=0; --i) all.push_back(v2[i]);

    int n; cin >> n;
    for(int i=0; i<n; ++i)
    {
        int res=-1;
        int low, high; cin >> low >> high;
        for(int x=int(all.size()-1); x>=0; x--)
            if (low <= all[x] && all[x] <= high) { res=all[x]; break; }
        cout << res << endl;     
    }
}
int main()
{
    solve();
}
