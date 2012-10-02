// =========================================================
// 
//       Filename:  LIGHT.cpp
// 
//    Description:  http://www.codechef.com/SEP12/problems/LIGHT
// 
//        Version:  1.0
//        Created:  09/02/2012 11:39:46 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/02/2012, LI YAN
// 
// =========================================================

// binary search feasible height h
// check whether h is feasible
// use h to cut a segment [left, right]
// sort and merge all segments
// if one of the merged segment covers [L, R], then feasible
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

int N;
double L, R;

const int MAX=50000+5;
const double PI=3.1415926536;
const double EPS=1.0e-8;
double X[MAX], Y[MAX], Z[MAX];

typedef pair<double, double> pdd; 
vector<pdd> seg, merged;

template<class T>
void chmax(T &a, T b)
{
    a = (a>b)?a:b;
}
bool check(double h)
{
    seg.clear();
    for(int i=0; i<N; ++i) {
        double s = Y[i] * tan(Z[i]*PI/180);
        double d, x1, x2;
        d = s * (1-h/Y[i]); if (d<EPS) continue;
        x1 = X[i] - d; x2 = X[i] + d;
        seg.push_back(pdd(x1, x2));
    }
    if (seg.empty()) return false;
    sort(seg.begin(), seg.end());
    merged.clear(); merged.push_back(seg[0]);
    for(int i=1; i<(int)seg.size(); ++i) {
        if (seg[i].first <= merged.back().second + EPS) {
            chmax(merged.back().second, seg[i].second);
        }
        else {
            merged.push_back(seg[i]);
        }
    }
    for(int i=0; i<(int)merged.size(); ++i) {
        double l, r;
        l = merged[i].first; r = merged[i].second;
        if (l-EPS <= L && R <= r+EPS) return true;
    }
    return false;
}

int main()
{
    assert(scanf("%d", &N)==1);
    assert(scanf("%lf%lf", &L, &R)==2);

    double lo, hi;
    lo = hi = 0;
    for(int i=0; i<N; ++i) {
        assert(scanf("%lf%lf%lf", X+i, Y+i, Z+i)==3);
        hi = max(hi, Y[i]);
    }

    for(int i=0; i<100; ++i) {
        double m = (lo+hi)/2;
        if (check(m)) lo=m;
        else hi=m;
    }
    printf("%.10f\n", lo);
}

// 
// Correct Answer
// Execution Time: 22.18 
