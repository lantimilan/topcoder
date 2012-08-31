// =========================================================
// 
//       Filename:  prob70C.cpp
// 
//    Description:  C. Beaver Game
// 
//        Version:  1.0
//        Created:  04/27/2011 09:57:32 AM
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

bool hasmove(int m, int minv)
{
    if (m<=minv) return false;
    if (minv==1) return true;
    for(int k=2; k<=sqrt(m); ++k)
        if (m%k==0 && m/k>=minv) return true;
    return false;
}

void solve()
{
    int n,m,k; cin >> n >> m >> k;
    int winner=1;

    // if n is even, then player 2 wins
    // else if (m,k) allows one move, then 
    // player 1 wins
    if (n%2) { 
        for(int c=1; c<=sqrt(m); ++c) if (m%c==0)
        { 
            int t = m/c;
            if (c>1 && t>=k && !hasmove(t,k)) winner=0; 
            if (t>1 && c>=k && !hasmove(c,k)) winner=0;
        }
    }

    if (winner == 0) cout << "Timur\n";
    else cout << "Marsel\n";
}

int main()
{
    solve();
}
