// =========================================================
// 
//       Filename:  prob6C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/18/2011 12:41:34 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/18/2011, LI YAN
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
    int n; cin >> n;
    VI bars(n);
    for(int i=0; i<n; ++i) cin >> bars[i];

    int sa=0,sb=0,a,b;
    for(a=0,b=n-1; a<=b; )
    {
        if (sa<sb) { sa+=bars[a++]; }
        else if (sa>sb) { sb+=bars[b--]; }
        else { sa+=bars[a++]; sb+=bars[b--]; }
    }
    //cout << sa << ' ' << sb << endl;
    cout << a << ' ' << (n-a) << endl;
}

int main()
{
    solve();
}
