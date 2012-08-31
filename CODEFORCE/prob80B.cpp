// =========================================================
// 
//       Filename:  prob69B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  04/19/2011 11:32:25 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/19/2011, LI YAN
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
    string s; cin >> s;
    double h = (s[0]-'0')*10 + s[1]-'0'; h = (h>=12) ? h-12 : h;
    double m = (s[3]-'0')*10 + s[4]-'0';
    h += m/60.0;
    cout << h/12*360 << " " << m/60*360 << endl;
}

int main()
{
    solve();
}
