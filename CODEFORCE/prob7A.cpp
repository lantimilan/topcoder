// =========================================================
// 
//       Filename:  prob7A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/19/2011 08:14:18 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/19/2011, LI YAN
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

template<class T>
void chmax(T &a, T b) { a = a>=b ? a:b; }

template<class T>
void chmin(T &a, T b) { a = a<=b ? a:b; }

int cntbit(int n)
{
    int ans=0;
    while(n) { ++ans; n&=n-1; }
    return ans;
}
void solve()
{
    vector<string> vs;
    string s;
    for(int i=0; i<8; ++i) { cin >> s; vs.PB(s); }
    int goal[8][8];
    for(int r=0; r<8; ++r) for(int c=0;c<8;++c)
        goal[r][c]=(vs[r][c]=='W')?0:1;

    int ans=100;
    for(int r=0; r<(1<<8); ++r)
    for(int c=0; c<(1<<8); ++c)
    {
        int nr=cntbit(r), nc=cntbit(c); //cout << nr << ' ' << nc << endl;
        int board[8][8]; memset(board,0,sizeof board);
        for(int i=0; i<8; ++i) if (r&1<<i)
            for(int k=0; k<8; ++k) board[i][k]=1;

        for(int i=0; i<8; ++i) if (c&1<<i)
            for(int k=0; k<8; ++k) board[k][i]=1;


        bool good=true;
        for(int i=0; i<8; ++i) for(int j=0; j<8; ++j)
            if (board[i][j]!=goal[i][j]) { good=false; goto done; }
        done:
        if (good) chmin(ans, nr+nc);
        //cout << ans << endl;
    }
    cout << ans << endl;
}

int main()
{
    solve();
}
