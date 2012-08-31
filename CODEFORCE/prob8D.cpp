// =========================================================
// 
//       Filename:  prob8D.cpp
// 
//    Description:  http://codeforces.com/contest/8/problem/D
// 
//        Version:  1.0
//        Created:  08/29/2011 04:11:04 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/29/2011, LI YAN
// 
// =========================================================

#include <cmath>
#include <iomanip>
#include <iostream>
#include <utility>
using namespace std;

typedef pair<double,double> pdd;

const double EPS=1.0e-6;

inline double sq(double x) { return x*x; }
inline double dist(pdd p1, pdd p2)
{
    return sqrt(sq(p1.first-p2.first) + sq(p1.second-p2.second));
}

inline pdd operator+(pdd p1, pdd p2)
{
    return pdd(p1.first+p2.first, p1.second+p2.second);
}
inline pdd operator-(pdd p1, pdd p2)
{
    return pdd(p1.first-p2.first, p1.second-p2.second);
}

pdd operator*(pdd p, double s)
{
    return pdd(p.first*s,p.second*s);
}
pdd operator*(pdd p1, pdd p2)
{
    double a=p1.first*p2.first-p1.second*p2.second;
    double b=p1.first*p2.second+p1.second*p2.first;
    return pdd(a,b);
}

pair<pdd,pdd> intersect(pdd p1, double r1, pdd p2, double r2)
{
    double d = dist(p1,p2);
    double tcos = (sq(r1)+sq(d)-sq(r2))/(2*r1*d);
    if (tcos>1.0) tcos=1.0;
    double tsin = sqrt(1.0-tcos);
    pdd ans1 = (p2-p1)*(r1/d)*(tcos+tsin)+p1;
    pdd ans2 = (p2-p1)*(r1/d)*(tcos-tsin)+p1;
    return make_pair(ans1,ans2);
}

int main()
{
    double t1, t2; cin >> t1 >> t2;
    pdd xy[3];
    cin >> xy[0].first >> xy[0].second; // cinema
    cin >> xy[2].first >> xy[2].second; // house
    cin >> xy[1].first >> xy[1].second; // shop
    double l1 = t1+dist(xy[0],xy[1]), l2=t2+dist(xy[0],xy[2]);

    cout << l1 << ' ' << l2 << endl;
    cout << dist(xy[1],xy[2]) << endl;

    double ans=0;
    double lo=0, hi=100;
    for(int i=0; i<1000; ++i)
    {
        cout << endl << "lo hi " << lo << ' ' << hi << endl;
        double mid = (lo+hi)/2; //cout << mid << endl;
        double h1=l1-mid,h2=l2-mid; cout << "h1h2 " << h1 << ' ' << h2 << endl;
        if (dist(xy[1],xy[2])>h1+h2+EPS) { hi=mid; continue; }
        pair<pdd,pdd> pts;
        pts = intersect(xy[1],h1,xy[2],h2);
        pdd p1=pts.first, p2=pts.second;
        double d1=dist(p1,xy[0])-mid, d2=dist(p2,xy[0])-mid;
        cout << "bsearch " << mid << ' ' << d1 << ' ' << d2 << endl;
        if (fabs(d1)<EPS) d1=0;
        if (fabs(d2)<EPS) d2=0;

        if (d1<=0||d2<=0) lo=mid;
        else hi=mid;

        ans=mid;
    }
    // add v[1] to v[2] if split point is at shop=v[1]
    if (fabs(ans-dist(xy[0],xy[1]))<EPS) ans+=dist(xy[1],xy[2]);
    cout << fixed << setprecision(6) << ans << endl;
}
