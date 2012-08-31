// =========================================================
// 
//       Filename:  prob8C.cpp
// 
//    Description:  http://codeforces.com/problemset/problem/8/C
// 
//        Version:  1.0
//        Created:  08/29/2011 12:17:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/29/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int x[30],y[30];
int dp[1<<24];
pii conf[1<<24];

int n;

int dist(int x1, int x2, int y1, int y2)
{
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int calc(int sub)
{
    if (sub==0) return 0;
    if (dp[sub]>0) return dp[sub];
    int &ans=dp[sub];
    ans=1000000;
    int i;
    for(i=0; i<n; ++i) if (sub&1<<i) break;

    for(int j=0; j<n; ++j) if (sub&1<<j)
    {
        int d = dist(x[0],x[i+1],y[0],y[i+1])
            + dist(x[i+1],x[j+1],y[i+1],y[j+1])
            + dist(x[j+1],x[0],y[j+1],y[0])
            + calc(sub^(1<<i|1<<j));
        if (d<ans) {
            ans=d; conf[sub]=pii(i,j);
        }
    }
    return ans;
}

int main()
{
    cin >> x[0] >> y[0];
    cin >> n;
    for(int i=1; i<=n; ++i) cin >> x[i] >> y[i];

    int ans = calc((1<<n)-1); cout << ans << endl;

    cout << 0;
    int sub=(1<<n)-1;
    while(sub) {
        pii p = conf[sub];
        cout << ' ' << p.first+1;
        if (p.second!=p.first) cout << ' ' << p.second+1;
        cout << ' ' << 0;
        sub^=(1<<p.first|1<<p.second);
    }
    cout << endl;
}

// 650117   Aug 29, 2011 11:45:38 PM    lantimilan  C - Looking for Order   GNU
// C++  Accepted    190 ms  198400 KB
//
// this one introduces an unnecessary nested loop in calc
//
// 650069   Aug 29, 2011 11:39:27 PM    lantimilan  C - Looking for Order   GNU
// C++  Time limit exceeded on test 12  7500 ms     198400 KB
//
// this one forget to return dp[key] when already seen
//
// 650061   Aug 29, 2011 11:37:32 PM    lantimilan  C - Looking for Order   GNU
// C++  Time limit exceeded on test 12  7500 ms     198400 KB
//
// finally figured out the restriction the person cannot take more than 2
// objects at the same time
//
// 641465   Aug 29, 2011 11:50:11 AM    lantimilan  C - Looking for Order   GNU
// C++  Wrong answer on test 4  30 ms   9600 KB
// 641452   Aug 29, 2011 11:41:42 AM    lantimilan  C - Looking for Order   GNU
// C++  Compilation error   0 ms    0 KB 
