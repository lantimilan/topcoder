// =========================================================
// 
//       Filename:  prob70D.cpp
// 
//    Description:  D. Archer's Shot
// 
//        Version:  1.0
//        Created:  04/27/2011 09:16:43 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/27/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

void solve()
{
    LL n; cin >> n;
    LL cnt = 0;
    LL xk, yk;
    for(xk=1; xk<=(2*n-1)/3; ++xk)
    {
        double x=(xk*3+1)/2.0;
        double d = n*n-x*x;
        if (xk&1) { yk=LL(sqrt(d/3)); }
        else { yk=LL(sqrt(d/3)-0.5); }
        cnt += yk;
    }
    cnt *=4; cout << cnt << endl;
    LL k = LL(2*n/sqrt(3)-1)/2; cnt += 2*k;
    k = (n-1)/3; cnt += 2*k;
    cnt++;
    cout << cnt << endl;
}

int main()
{
    solve();
}
