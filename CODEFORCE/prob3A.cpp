// =========================================================
// 
//       Filename:  prob3A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/29/2011 11:14:10 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/29/2011, LI YAN
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
    string s, t; cin >> s >> t;
    PII start, term;
    start.first = s[0]-'a'; start.second = s[1]-'1';
    term.first = t[0]-'a'; term.second = t[1]-'1'; 

    int ncol = abs(start.first-term.first);
    int nrow = abs(start.second-term.second);
    int diag = min(nrow,ncol), lat = abs(nrow-ncol);
    int n = diag + lat;
    cout << n << endl;

    string m1, m2;
    if (start.first >= term.first && start.second < term.second) m1 = "LU";
    else if (start.first >= term.first && start.second >= term.second) m1 = "LD";
    else if (start.first < term.first && start.second < term.second) m1 = "RU";
    else m1 = "RD";

    if (nrow < ncol) { if (start.first < term.first) m2 = "R"; else m2 = "L"; }
    else { if (start.second < term.second) m2 = "U"; else m2 = "D"; }
    
    for(int i=0; i<diag; ++i) cout << m1 << endl;
    for(int i=0; i<lat; ++i) cout << m2 << endl;
}

int main()
{
    solve();
}
