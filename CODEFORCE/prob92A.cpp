// =========================================================
// 
//       Filename:  prob92A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/26/2011 11:27:42 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/26/2011, LI YAN
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

void solve()
{
    int n, m; cin >> n >> m;
    int sum = n*(n+1)/2;
    m %= sum;
    for(int i=1; i<=n; ++i)
    {
        if (m<i) break;
        m -= i;
    }
    cout << m << endl;
}

int main()
{
    solve();
}
