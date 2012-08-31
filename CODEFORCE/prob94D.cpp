// =========================================================
// 
//       Filename:  D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/30/2011 08:48:17 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/30/2011, LI YAN
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
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef pair<int,int> PII;

#define EPS 1.0e-7
#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair
#define sz(x) int(x.size())

void solve()
{
    double n, w, m; cin >> n >> w >> m;
    double avg = n*w/m; //cout << avg << endl;

    vector<vector<pair<int,double> > > vv;
    double cup=0, bottle=w, cnt=0; 
    vector<pair<int,double> > vec;
    for(int i=0; i<n; ) {
        double fill;
        double need = avg-cup;
        if (need <= bottle) fill = need; else fill = bottle;
        vec.PB(MP((i+1),fill));
        bottle-=fill; cup+=fill; cnt++; 
        if (cnt > 2) { cout << "NO\n"; return; }

        if (fabs(bottle) < EPS) { bottle=w; ++i; cnt=0; }
        if (fabs(cup-avg) < EPS) { cup=0; vv.PB(vec); vec.clear(); }
        //cout << cup << " " << bottle << " " << fill << " " << cnt << endl;
    }
    cout << "YES\n"; assert(vv.size()==m);
    for(int i=0; i<m; ++i) {
        for(int k=0; k<sz(vv[i]); ++k)
        { if (k) cout << ' '; cout << vv[i][k].first << ' ' << fixed << setprecision(7) << vv[i][k].second; }
        cout << endl;
    }
}

int main()
{
    solve();
}
