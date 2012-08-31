// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/08/2011 09:15:06 AM
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

bool match(string s1, string s2)
{
    if (s1.size() != s2.size()) return false;
    for(int i=0; i<sz(s1); ++i)
        if (tolower(s1[i]) != tolower(s2[i])) return false;
    return true;
}
void solve()
{
    int n; cin >> n;
    vector<string> forbid(n);
    for(int i=0; i<n; ++i) cin >> forbid[i];
    string w; cin >> w;
    string ss; cin >> ss; char letter=ss[0];

    int len = w.size(); vector<int> mark(len,0);
    for(int l=0; l<len; ++l) for(int r=l+1; r<=len; ++r)
    {
        bool bad=false;
        string sub = w.substr(l,r-l);
        for(int i=0; i<n; ++i) {
            if (match(forbid[i],sub)) { bad=true; break; }
        }
        if (bad) for(int i=l; i<r; ++i) mark[i]=1;
    }

    char cap, lower; 
    cap = toupper(letter); lower = tolower(letter);
    for(int i=0; i<sz(w); ++i) if (mark[i]) {
        char ch = w[i];
        if (isupper(ch)) {
            if (ch != cap) w[i] = cap;
            else { if (cap=='A') w[i]='B'; else w[i]='A'; }
        }
        else {
            if (ch != lower) w[i] = lower;
            else { if (lower=='a') w[i]='b'; else w[i]='a'; }
        }
    }
    cout << w << endl;
}

int main()
{
    solve();
}
