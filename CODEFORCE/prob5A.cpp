// =========================================================
// 
//       Filename:  prob5A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2011 01:38:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/14/2011, LI YAN
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
    set<string> names;
    string s;
    int ans=0;
    while(getline(cin,s)) {
        if (s[0] == '+') { 
            string name = s.substr(1); names.insert(name);
        } else if (s[0]=='-') {
            string name = s.substr(1); names.erase(name);
        } else {
            int p; for(p=0; p<sz(s) && s[p]!=':'; ++p);
            string msg=s.substr(p+1);
            ans += sz(names)*sz(msg);
        }
    }
    cout << ans << endl;
}

int main()
{
    solve();
}
