// =========================================================
// 
//       Filename:  LEBOBBLE.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/04/2012 06:30:08 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/04/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int n, d;
int B[50005];
int P[50005];
vector<pii> right;
vector<double> sum;

double calc(int begin, int end)
{
    if (begin+1>=end) return 0.0;
    double ans=0.0;
    int m=(begin+end)/2;
    ans += calc(begin, m);
    ans += calc(m, end);
    right.clear();
    for(int i=m; i<end; ++i)
        right.push_back(pii(B[i], P[i]));
    sort(right.begin(), right.end());

    sum.resize(right.size()+1);
    sum[0]=0;
    for(int i=1; i<=int(right.size()); ++i)
        sum[i]=sum[i-1]+right[i-1].second;
    for(int i=0; i<int(sum.size()); ++i)
        sum[i]/=100.0;

    for(int i=begin; i<m; ++i) {
        double p = P[i]/100.0;
        int s;
        vector<pii>::const_iterator it;
        // both B[i] or B[i]+d
        it = lower_bound(right.begin(), right.end(), pii(B[i], 0));
        s = it-right.begin();
        ans += (1-p)*(s-sum[s]);
        ans += p*sum[s];
        // left B[i] and right is B[i]+d
        it = lower_bound(right.begin(), right.end(), pii(B[i]-d, 0));
        s = it-right.begin();
        ans += (1-p)*sum[s];
        // left B[i]+d and right is B[i]
        it = lower_bound(right.begin(), right.end(), pii(B[i]+d, 0));
        s = it-right.begin();
        ans += p*(s-sum[s]);
    }
    return ans;
}

void solve()
{
    scanf("%d%d", &n, &d);
    for(int i=0; i<n; ++i)
        scanf("%d", B+i);
    for(int i=0; i<n; ++i)
        scanf("%d", P+i);
    double ans = calc(0,n);
    printf("%.4f\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}

// WA, because of floating point precision?
// yes, see the accepted version
