// =========================================================
// 
//       Filename:  prob4C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/12/2011 05:20:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/12/2011, LI YAN
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

void solve()
{
    map<string,int> db;
    int n; cin >> n;
    string user;
    for(int i=0; i<n; ++i) { cin >> user;
        if (db.count(user)) {
            int cnt = ++db[user]; cout << user << cnt-1 << endl;
        }
        else {
            db[user]=1; cout << "OK" << endl;
        }
    }
}

int main()
{
    solve();
}
