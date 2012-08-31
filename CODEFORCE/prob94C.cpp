// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/30/2011 08:27:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/30/2011, LI YAN
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
#define sz(x) int(x.size())

void solve()
{
    int n,m,a,b; cin >> n >> m >> a >> b;
    int ans=0;
    int a1 = (a+(m-1))/m;
    int b1 = (b+(m-1))/m;

    if (m==1) ans=1;
    else if (a1==b1) ans=1;
    else if (a%m==1 && (b%m==0 || b==n)) ans=1;
    else if (a1+1==b1) ans=2;
    else if (a%m==1) ans=2;
    else if (b%m==0 || b==n) ans=2;
    else if (a%m==(b+1)%m) ans=2;
    else ans=3;

    cout << ans << endl;
}

int main()
{
    solve();
}
