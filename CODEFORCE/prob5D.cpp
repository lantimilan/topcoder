// =========================================================
// 
//       Filename:  prob5D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/15/2011 09:04:27 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/15/2011, LI YAN
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

template<class T>
void chmax(T &a, T b) { a = a>=b ? a:b; }

template<class T>
void chmin(T &a, T b) { a = a<=b ? a:b; }

void solve()
{
    int a, v; cin >> a >> v;
    int l, d, w; cin >> l >> d >> w;

    double t = sqrt(2.0*d/a);
    double vd = min(1.0*v,a*t);
    double ans;
    if (vd <= w) {
        double tall = sqrt(2.0*l/a);
        double vmax = a*tall;
        if (v>=vmax) ans = tall;
        else {
            double t1 = (double)v/a;
            double s1 = .5*a*t1*t1;
            double t2 = (l-s1)/v;
            ans = t1+t2;
        }

    }
    else {
        // the red solution mostly get
        // dist: 0 to v then to w
        // then compare dist to d
        // if d < dist
        // then run binary search for 100 iterations
        //
        // also can binary search vmax < v
        // without solving quadratic equation
        //
        const double EPS=1.0e-6;
        double lo=w, hi=v, mid, dist=0;
        double t1, t2;
        while(lo<hi-EPS) {
            mid=(lo+hi)/2.0;
            t1 = mid/a; t2 = (mid-w)/a; assert(t2>=0);
            dist = .5*a*t1*t1;
            dist += w*t2 + .5*a*t2*t2;

            //cout << lo << ' ' << hi << ' ' << dist << ' ' << d << endl;
            //cout << t1 << ' ' << t2 << endl;
            if (dist > d) hi=mid;
            else if (dist < d) lo=mid;
            else break;
        }
        //cout << t1 << ' ' << t2 << endl;
        //cout << fixed << setprecision(10) << dist << ' ' << d << endl;
        if (dist+EPS*d<(double)d) { // use relative EPS here
        // acc to v, cruise v, dec to w
            t1 = (double)v/a;
            double s1 = .5*a*t1*t1;
            t2 = double(v-w)/a; s1+=w*t2+.5*a*t2*t2;
            t2 += (d-s1)/v;
        }
        //cout << t1 << ' ' << t2 << endl;
        double t3 = (-w+sqrt(w*w+2.0*a*(l-d)))/a; // previously missed a in 2.0*a
        if (v>=w+a*t3) ans = t1 + t2 + t3;
        else {
            t3 = double(v-w)/a;
            double t4 = ((l-d)-(w*t3+.5*a*t3*t3))/v; // previously missed a in .5*a
            ans = t1+t2+t3+t4;
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
}

int main()
{
    solve();
}

/* ************
 * 548179   Jul 16, 2011 10:32:21 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Accepted    30 ms   1400 KB
 * 548177   Jul 16, 2011 10:31:19 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Wrong answer on test 2  10 ms   1400 KB
 * 548175   Jul 16, 2011 10:25:20 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Wrong answer on test 11     30 ms   1400 KB
 * 548171   Jul 16, 2011 10:19:10 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Wrong answer on test 3  10 ms   1400 KB
 * 548170   Jul 16, 2011 10:18:21 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Wrong answer on test 2  10 ms   1400 KB
 * 548167   Jul 16, 2011 10:11:08 AM    lantimilan  D - Follow Traffic Rules
 * GNU C++  Wrong answer on test 11     30 ms   1400 KB 
 * */
