// =========================================================
// 
//       Filename:  prob79A.cpp
// 
//    Description:  A. Bus Game
// 
//        Version:  1.0
//        Created:  04/30/2011 08:01:00 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/30/2011, LI YAN
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

void solve()
{
    int x, y; cin >> x >> y;
    int turn=0, winner=0;
    while(1)
    {
        if (turn==0) { 
            if (x>=2) { if (y>=2) {x-=2; y-=2;} else { winner=1-turn; break;} }
            else if (x==1) { if (y>=12) {x-=1; y-=12;} else {winner=1-turn; break;}}
            else { if (y>=22) y-=22; else {winner=1-turn; break;} }
        }
        else {
            if (y>=22) { y-=22; }
            else if (y>=12) { if (x>=1) {y-=12; x-=1;} else { winner=1-turn; break;}}
            else { if (x>=2 && y>=2) {x-=2; y-=2;} else {winner=1-turn; break;}}
        }
        turn = 1-turn;
    }
    if (winner==0) cout << "Ciel" << endl;
    else cout << "Hanako" << endl;
}

int main()
{
    solve();
}
