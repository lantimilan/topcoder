// =========================================================
// 
//       Filename:  prob99E.cpp
// 
//    Description:  E. Help Greg the Dwarf
// 
//        Version:  1.0
//        Created:  07/23/2011 11:28:38 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/23/2011, LI YAN
// 
// =========================================================

// 1. draw a picture and get the formula for w
// w = b*cos(theta) + a*sin(theta)-l*cos(theta)*sin(theta)
// 2. do ternary search for theta that minimize w, since w cannot 
// be larger than f(theta) for any theta from 0 to pi/2
// 3. one special case is l<=min(a,b), in this case w=l as w<=l and 
// the rectangle can go through without rotating
//
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

template<class T>
void chmin(T &a, T b)
{ a=a<=b?a:b; }

template<class T>
void chmax(T &a, T b)
{ a=a>=b?a:b; }

double calc(double a, double b, double l, double theta)
{
    return b*cos(theta)+a*sin(theta)-l*cos(theta)*sin(theta);
}
void solve()
{
    double a, b, l; cin >> a >> b >> l;
    double ans=0;
    if (l<=a) ans=b;
    else if (l<=b) ans=a;

    // ternary search
    double r1=0, r2=acos(0);
    for(int i=0; i<1000; ++i)
    {
        double r11=2.0/3*r1+1.0/3*r2;
        double r22=1.0/3*r1+2.0/3*r2;
        if (calc(a,b,l,r11)>calc(a,b,l,r22)) r1=r11; // throw left 1/3
        else r2=r22; // throw right 1/3
    }
    chmax(ans, calc(a,b,l,r1)); // the calc could be <0
    chmin(ans, l);
    if (fabs(ans)<=1.0e-7) cout << "My poor head =(" << endl;
    else cout << fixed << setprecision(10) << ans << endl;
}
int main()
{
    solve();
}
