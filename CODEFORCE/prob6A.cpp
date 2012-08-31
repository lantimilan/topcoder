// =========================================================
// 
//       Filename:  prob6A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/18/2011 12:15:05 AM
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
    int ans=-1; // 1 tri, 0 seg, -1 imp
    int a[4]; for(int i=0; i<4; ++i) cin >> a[i];
    sort(a,a+4);
    for(int i=0; i<4; ++i)
    {
        int b[3], nb=0;
        for(int j=0; j<4; ++j) if (j!=i) b[nb++] = a[j];
        if (b[0]+b[1] > b[2]) ans=1;
        else if (b[0]+b[1]==b[2] && ans<0) ans=0;
    }
    if (ans==1) cout << "TRIANGLE\n";
    else if (ans==0) cout << "SEGMENT\n";
    else cout << "IMPOSSIBLE\n";
}

int main()
{
    solve();
}
