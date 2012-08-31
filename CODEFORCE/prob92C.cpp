// =========================================================
// 
//       Filename:  prob92C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/26/2011 12:09:46 PM
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
#define sz(s) int(s.size())

void solve()
{
    string s1, s2; cin >> s1 >> s2;
    int cnt[2][30]; memset(cnt, 0, sizeof cnt);
    for(int i=0; i<sz(s1); ++i) cnt[0][s1[i]-'a']++;
    for(int i=0; i<sz(s2); ++i) cnt[1][s2[i]-'a']++;
    VI alpha[30];
    for(int i=0; i<sz(s1); ++i) alpha[s1[i]-'a'].PB(i);

    for(char ch='a'; ch<='z'; ++ch)
        if (cnt[1][ch-'a'] && !cnt[0][ch-'a']) 
            { cout << -1 << endl; return; }

    int ans=1,pos=-1;
    for(int p2=0; p2<sz(s2); ++p2)
    {
        char ch = s2[p2];
        VI &vec=alpha[ch-'a'];
        VI::const_iterator it = lower_bound(vec.begin(), vec.end(), pos+1);
        if (it==vec.end()) { ans++; pos = vec[0]; }
        else pos=*it;
    }
    cout << ans << endl;
}

int main()
{
    solve();
}
