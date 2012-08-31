// =========================================================
// 
//       Filename:  prob2B.cpp
// 
//    Description:  B. The least round way
// 
//        Version:  1.0
//        Created:  03/15/2011 10:50:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/15/2011, LI YAN
// 
// =========================================================
//

#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>

using namespace std;

#define MAXN 1000+5
#define INF 20000000

typedef pair<int,int> PII;

PII matrix[MAXN][MAXN]; // two,five
PII dp[MAXN][MAXN][2]; // 0 is (min2*,min5), 1 is (min2,min5*)

inline PII operator+(PII a, PII b)
{ return PII(a.first+b.first, a.second+b.second); }

inline PII operator-(PII a, PII b)
{ return PII(a.first-b.first, a.second-b.second); }

ostream& operator<<(ostream& os, PII p)
{ return os << "(" << p.first << "," << p.second << ")"; }

// is function call too expensive
// still TLE after removing function call
PII reduce(int n)
{
    int two=0, five=0;
    while(n%2==0) { n/=2; two++; }
    while(n%5==0) { n/=5; five++; }
    return PII(two,five);
}

void solve()
{
    int res=INF, rzero=-1, czero=-1;
    int n; cin >> n;
    for(int r=0; r<n; ++r) for(int c=0; c<n; ++c)
    { 
        int k; cin >> k;
        if (k==0) { res=1; rzero=r; czero=c; k=10; }
        matrix[r][c] = reduce(k);
    }

    dp[0][0][0] = dp[0][0][1] = matrix[0][0];
    for(int r=1; r<n; ++r) for(int k=0; k<2; ++k)
        dp[r][0][k] = dp[r-1][0][k] + matrix[r][0];
    for(int c=1; c<n; ++c) for(int k=0; k<2; ++k)
        dp[0][c][k] = dp[0][c-1][k] + matrix[0][c];

    for(int r=1; r<n; ++r)
    for(int c=1; c<n; ++c)
    {
            PII up[2], left[2];
            for(int k=0; k<2; ++k) { up[k] = dp[r-1][c][k]; left[k] = dp[r][c-1][k]; }
            int n2 = matrix[r][c].first, n5 = matrix[r][c].second;
            int a2 = up[0].first  + n2;
            int a5 = up[0].second + n5;
            int b2 = left[0].first  + n2;
            int b5 = left[0].second + n5;
            if (a2 < b2 || (a2==b2 && a5<=b5)) dp[r][c][0] = PII(a2,a5);
            else dp[r][c][0] = PII(b2,b5);
            a2 = up[1].first  + n2;
            a5 = up[1].second + n5;
            b2 = left[1].first  + n2;
            b5 = left[1].second + n5;
            if (a5 < b5 || (a5==b5 && a2<=b2)) dp[r][c][1] = PII(a2,a5);
            else dp[r][c][1] = PII(b2,b5);
    }

    int best = res, bit;
    for(int k=0; k<2; ++k)
    {
        PII last = dp[n-1][n-1][k];
        int x = min(last.first, last.second);
        if (x < best) { best = x; bit = k;}
    }
    cout << best << endl;
    if (best==res) // pass an entry of value zero
    {
        string path;
        path += string(czero,'R') + string(n-1,'D') + string(n-1-czero,'R');
        cout << path << endl;
        return;
    }
    int r,c,b; r=c=n-1; b=bit;
    string path;
    while(r+c)
    {
        PII prev = dp[r][c][b]-matrix[r][c];
        if (r>0 && dp[r-1][c][0] == prev) { r--; b=0; path+='D'; }
        else if (r>0 && dp[r-1][c][1] == prev) { r--; b=1; path+='D'; }
        else if (c>0 && dp[r][c-1][0] == prev) { c--; b=0; path+='R'; }
        else { c--; b=1; path+='R'; }
    }
    reverse(path.begin(), path.end());
    cout << path << endl;
}

int main()
{
    solve();
}

/***********************
 * Previously got a lot of TLEs, thought about all possible optimizations.
 * the real issue was to handle zero correctly !!
 *
 * TODO: the min(INF,...) looks ugly, anyway to get around it?
 * Answer: replace 0 by 10, then any solution that uses this modified entry  is
 * no better than a path that uses 0, since that path has only one zero.
 *
 * cleaned up a bit
 * 353826        Mar 25, 2011 4:44:14 AM    lantimilan        2B - The least
 * round way     GNU C++     Accepted        3190 ms     25100 KB 
 *
 * 353823        Mar 25, 2011 4:33:45 AM    lantimilan        2B - The least
 * round way     GNU C++     Accepted        3230 ms     25100 KB 
 *
 * 353813        Mar 25, 2011 3:24:56 AM    lantimilan        2B - The least
 * round way     GNU C++     Time limit exceeded on test 31      5000 ms
 * 25100 KB 
 *
 * 353810        Mar 25, 2011 3:01:28 AM    lantimilan        2B - The least
 * round way     GNU C++     Time limit exceeded on test 31      5000 ms
 * 25100 KB 
 *
 * 353799        Mar 25, 2011 1:59:10 AM    lantimilan        2B - The least
 * round way     GNU C++     Wrong answer on test 5      50 ms       21100 KB 
 *
 * 353791        Mar 25, 2011 1:24:32 AM    lantimilan        2B - The least
 * round way     GNU C++     Wrong answer on test 3      30 ms       21100 KB 
 353726      Mar 24, 2011 10:23:23 PM   lantimilan        2B - The least round way       GNU C++     Wrong answer on test 3      30 ms       21100 KB 
 **************************/
