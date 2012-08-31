// =========================================================
// 
//       Filename:  prob5E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/16/2011 10:28:05 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/16/2011, LI YAN
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
#include <stack>
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
    int n; cin >> n;
    VI a(n);
    int p=0,q;
    for(int i=0; i<n; ++i) { 
        cin >> a[i];
        if (a[i]>a[p]) p=i;
    }
    rotate(a.begin(), p+a.begin(), a.end()); //cout << "max " << a[0] << endl;
    LL ans=0LL;

    //for(int i=0; i<n; ++i) cout << a[i] << ' '; cout << endl;
    int left=0, right=0, pos=0;
    for(p=1; p<n; ++p) if (a[p]>=left) { ++ans; left=a[p]; pos=p; }
    for(q=n-1; q>pos; --q) if (a[q]>=right) { ++ans; right=a[q]; }

    //cout << "with max " << ans << endl;

    stack<PII> prev;
    for(p=1; p<n; ++p)
    {
        int cnt=1;
        while(!prev.empty()) {
            int v = prev.top().first;
            int c = prev.top().second;
            if (v<a[p]) { ans+=c; prev.pop(); }
            else if (v==a[p]) { ans+=c; prev.pop(); cnt+=c; }
            else { ans++; break; }
        }
        prev.push(PII(a[p],cnt)); 
        //cout << prev.top().first << ' ' << prev.top().second << endl;
    }
    cout << ans << endl;
}

int main()
{
    solve();
}

// could have duplicate elements
