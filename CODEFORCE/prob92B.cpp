// =========================================================
// 
//       Filename:  prob92B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/26/2011 11:35:54 AM
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
    string s; cin >> s; assert(s[0]=='1');
    reverse(s.begin(), s.end());
    int N = s.size();
    int ans=0;
    for(int i=0; i<N-1; ++i) {
        if (s[i]=='0') ans++;
        else {
            ans++; s[i]='0'; ans++;
            for(int j=i+1; j<N; ++j) {
                if (s[j]=='0') { s[j]='1'; break; }
                else s[j]='0';
            }
        }
    }
    if (s[N-1]=='0') ans++;
    cout << ans << endl;
}

int main()
{
    solve();
}
