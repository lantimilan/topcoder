// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/30/2011 08:05:53 AM
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
    string text; cin >> text;
    map<string,int> mp;
    string src;
    for(int i=0; i<10; ++i) { cin >> src; mp[src]=i; }

    for(int i=0; i<8; ++i) {
        string sub = text.substr(i*10, 10); //cout << sub << endl;
        cout << mp[sub];
    }
    cout << endl;
}

int main()
{
    solve();
}
