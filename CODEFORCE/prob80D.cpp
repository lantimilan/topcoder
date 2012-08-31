// =========================================================
// 
//       Filename:  prob69D.cpp
// 
//    Description:  Falling Anvils 
// 
//        Version:  1.0
//        Created:  04/19/2011 10:43:51 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/19/2011, LI YAN
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
    int T; cin >> T;
    for(int t=0; t<T; ++t)
    {
        double a,b; cin >> a >> b;
        double ans = 0.0;
        double lim = min(a,4*b);
        ans += lim*lim/8.0+b*lim;
        if (a>4*b) ans += 2*b*(a-4*b);
        if (b==0) ans=1.0;
        else if (a==0) ans = 0.5;
        else ans /= 2*a*b;
        cout << fixed << setprecision(10) << ans << endl;
    }
}

int main()
{
    solve();
}

/* ********** */
