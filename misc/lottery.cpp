// =========================================================
// 
//       Filename:  lottery.cpp
// 
//    Description:  spotify puzzle
//    http://www.spotify.com/us/jobs/tech/ticket-lottery/
// 
//        Version:  1.0
//        Created:  09/15/2012 01:28:26 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2012, LI YAN
// 
// =========================================================

// pr = sum_j=w^p (p choose j)*(m-p choose n-j) / (m choose n)
// where w = ceil(p/t)
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

double mydiv(const vector<int>& num, const vector<int>& deno) {
    double ans = 1.0;
    int i, j;
    for(i=0, j=0; i<(int)num.size() && j<(int)deno.size();) {
        if (ans < 1.0) { ans *= num[i++]; }
        else { ans /= deno[j++]; }
    }
    for(; i<(int)num.size(); ++i)
        ans *= num[i];
    for(; j<(int)deno.size(); ++j)
        ans /= deno[j];
    return ans;
}

int main()
{
    int m, n, t, p;
    assert(scanf("%d%d%d%d", &m, &n, &t, &p) == 4);
    int w = (p+t-1)/t;
    double ans = 0.0;
    for(int j=w; j<=p; ++j) if (j<=n && m-p >= n-j) {
        vector<int> num, deno;
        for(int i=m; i>m-n; --i) deno.push_back(i);
        for(int i=1; i<=j; ++i) deno.push_back(i);
        for(int i=1; i<=n-j; ++i) deno.push_back(i);
        for(int i=p; i>p-j; --i) num.push_back(i);
        for(int i=m-p; i>m-p-(n-j); --i) num.push_back(i);
        for(int i=n; i>0; --i) num.push_back(i);
        ans += mydiv(num, deno);
    }
    printf("%.10f\n", ans);
}

// Accepted
