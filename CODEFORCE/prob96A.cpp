// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2011 08:05:52 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/08/2011, LI YAN
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
    string s; cin >> s;
    char ch = s[0]; int cnt=1;

    bool danger=false;
    for(int i=1; i<sz(s); ++i)
    {
        if (s[i]==ch) { cnt++; if (cnt>=7) danger=true; }
        else { ch=s[i]; cnt=1; }
    }
    if (danger) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    solve();
}
