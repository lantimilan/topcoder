// =========================================================
// 
//       Filename:  prob3C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/11/2011 09:28:28 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/11/2011, LI YAN
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
    string board[3];
    for(int i=0; i<3; ++i) cin >> board[i];

    int a=0,b=0;
    for(int i=0; i<3; ++i) for(int j=0; j<3; ++j)
    { a+=(board[i][j]=='X'); b+=(board[i][j]=='0'); }

    if (a==b || a==b+1) {
        bool three[2] = {false, false};
        // row
        for(int r=0; r<3; ++r)
        {
            char ch = 'X';
            int c;
            for(c=0; c<3; ++c) if (board[r][c]!=ch) break;
            if (c>=3) three[0]=true;
            ch = '0';
            for(c=0; c<3; ++c) if (board[r][c]!=ch) break;
            if (c>=3) three[1]=true;
        }
        // col
        for(int c=0; c<3; ++c)
        {
            char ch = 'X';
            int r;
            for(r=0; r<3; ++r) if (board[r][c]!=ch) break;
            if (r>=3) three[0]=true;
            ch = '0';
            for(r=0; r<3; ++r) if (board[r][c]!=ch) break;
            if (r>=3) three[1]=true;
        }
        // diag
        {
            char ch='X';
            int x;
            for(x=0; x<3; ++x) if (board[x][x]!=ch) break;
            if (x>=3) three[0]=true;
            ch = '0';
            for(x=0; x<3; ++x) if (board[x][x]!=ch) break;
            if (x>=3) three[1]=true;

            int r,c;
            ch = 'X';
            for(r=0,c=2; r<3&&c>=0; ++r,--c)
                if (board[r][c]!=ch) break;
            if (r>=3) three[0]=true;
            ch = '0';
            for(r=0,c=2; r<3&&c>=0; ++r,--c)
                if (board[r][c]!=ch) break;
            if (r>=3) three[1]=true;
        }
        if (three[0] && three[1]) cout << "illegal" << endl;
        else if (three[0]) {
            if (a==b+1) cout << "the first player won" << endl;
            else cout << "illegal" << endl;
        }
        else if (three[1]) { 
            if (a==b) cout << "the second player won" << endl;
            else cout << "illegal" << endl;
        }
        else {
            if (a+b==9) cout << "draw" << endl;
            else if (a==b) cout << "first" << endl;
            else cout << "second" << endl;
        }
    } 
    else {
        cout << "illegal" << endl;
    }
}

int main()
{
    solve();
}
