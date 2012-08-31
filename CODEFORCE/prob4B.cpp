// =========================================================
// 
//       Filename:  prob4B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/12/2011 04:32:16 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/12/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define sz(x) int(x.size())

int f[40][300];

void solve()
{
    int d, sum; cin >> d >> sum;
    VI tmin(d+1), tmax(d+1);
    for(int i=1; i<=d; ++i) cin >> tmin[i] >> tmax[i];

    memset(f, -1, sizeof f);
    f[0][0]=0;
    for(int t=1; t<=d; ++t)
    {
        for(int p=0; p<=sum; ++p) if (f[t-1][p]>=0)
        for(int m=tmin[t]; m<=tmax[t]; ++m)
            f[t][p+m] = p;
    }
    if (f[d][sum]>=0) {
        cout << "YES" << endl;
        VI ans;
        int total = sum;
        int t=d;
        while(t) {
            int amt = total - f[t--][total];
            ans.PB(amt);
            total -= amt;
        }
        reverse(ans.begin(), ans.end());
        for(int i=0; i<sz(ans); ++i) 
        { if (i) cout << ' '; cout << ans[i]; }
        cout << endl;
    }
    else cout << "NO" << endl;
}

int main()
{
    solve();
}
