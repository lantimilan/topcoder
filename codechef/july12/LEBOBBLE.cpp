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

typedef long long int64;
typedef pair<int,int> pii;

int n, d;
int B[50005];
int P[50005];
vector<pii> right;
vector<int> sum;

int64 calc(int begin, int end)
{
    if (begin+1>=end) return 0;
    int64 ans=0;
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

    for(int i=begin; i<m; ++i) {
        int p = P[i];
        int s;
        vector<pii>::const_iterator it;
        // both B[i] or B[i]+d
        it = lower_bound(right.begin(), right.end(), pii(B[i], 0));
        s = it-right.begin();
        ans += (100-p)*(100*s-sum[s]);
        ans += p*sum[s];
        // left B[i] and right is B[i]+d
        it = lower_bound(right.begin(), right.end(), pii(B[i]-d, 0));
        s = it-right.begin();
        ans += (100-p)*sum[s];
        // left B[i]+d and right is B[i]
        it = lower_bound(right.begin(), right.end(), pii(B[i]+d, 0));
        s = it-right.begin();
        ans += p*(100*s-sum[s]);
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
    double ans = calc(0,n)/10000.0;
    printf("%.4f\n", ans);
}

int main()
{
    int T; scanf("%d", &T);
    while(T--)
        solve();
}

// 
//
// Correct Answer
// Execution Time: 8.44
//
// This problem is evil.
// It asks for 4 digits after decimal point, consider all the multiplications,
// only P[i] has 2 digits, and you can do integer arithmetic for all
// multiplications and convert to double in the end by dividing 1.0*100*100
// if you use double you get WA, as n=50000 is enough to fail floating point
// arithmetic. 
//
// Also notice that ans can be as large as 50000^2 * 100 * 100, this is more
// than int, you need long long
