// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  Yandex 2011 Round 1
// 
//        Version:  1.0
//        Created:  05/20/2011 08:09:56 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/20/2011, LI YAN
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
    int n; cin >> n;
    if (n==1) { cout << "a\n" << "a\n" << "b\n" << "b\n"; return; }
    if (n==2) { for(int i=0; i<4; i++) cout << char('a'+i) << char('a'+i) << endl; return; }
    string s[4];
    if (n&1) { // n is odd
        for(int r=0; r<4; ++r) for(int c=0; c<(n-1)/2; ++c) 
        {
            char ch;
            if (r%2==0) ch = char('a'+c%2);
            else ch = char('c'+c%2);
            s[r] += ch; s[r] += ch;
        }
        s[0]="x"+s[0]; s[1]="x"+s[1];
        s[2]+="y"; s[3] += "y";
    }
    else { // n even
        for(int c=0; c<n/2; ++c) { 
            char ch = char('a'+c%2); s[0] += ch; s[0] += ch; s[2]+=ch; s[2]+=ch;
            ch = char('c'+c%2); s[3] += ch; s[3] += ch; s[1]+=ch; s[1]+=ch;
        }
        s[1] = s[1].substr(2); s[1] = "x"+s[1]; s[1]+="y";
        s[2] = s[2].substr(2); s[2] = "x"+s[2]; s[2]+="y";
    }
    for(int i=0; i<4; ++i) cout << s[i] << endl;
}

int main()
{
    solve();
}
