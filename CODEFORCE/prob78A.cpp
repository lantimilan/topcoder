// =========================================================
// 
//       Filename:  prob70A.cpp
// 
//    Description:  A. Haiku
// 
//        Version:  1.0
//        Created:  04/27/2011 08:02:50 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/27/2011, LI YAN
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

bool isvowel(char ch)
{
    string vowel="aeiou";
    for(int i=0; i<int(vowel.size()); ++i)
        if (ch==vowel[i]) return true;
    return false;
}
void solve()
{
    vector<string> vs(3);
    for(int i=0; i<3; ++i) getline(cin,vs[i]);
    int cnt[3] = {0};

    for(int i=0; i<3; ++i)
    {
        for(int k=0; k<int(vs[i].size()); ++k)
            cnt[i] += (isvowel(vs[i][k]));
    }
    if (cnt[0]==5 && cnt[1]==7 &&cnt[2]==5) cout << "YES\n";
    else cout << "NO\n";
}

int main()
{
    solve();
}
