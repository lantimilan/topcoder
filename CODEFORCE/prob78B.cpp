// =========================================================
// 
//       Filename:  prob70B.cpp
// 
//    Description:  B. Easter Eggs
// 
//        Version:  1.0
//        Created:  04/27/2011 08:11:39 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/27/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

void solve()
{
    int n; cin >> n;
    string colors="ROYGBIV";

    string paint(n,'R');
    for(int i=0; i<n; ++i)
        paint[i] = colors[i%4];
    for(int i=n-1,j=6; i>=n-3; --i,--j)
        paint[i] = colors[j];
    cout << paint << endl;
}

int main()
{
    solve();
}
