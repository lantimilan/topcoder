// =========================================================
// 
//       Filename:  C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/22/2011 09:40:56 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/22/2011, LI YAN
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

// draw a cube
// top 1
// bottom 6
// front 2 back 4
// left 5 right 3
int matrix[24][6] = {
{1,2,5,4,3,6},
{1,5,4,3,2,6},
{1,4,3,2,5,6},
{1,3,2,5,4,6},
{6,3,4,5,2,1},
{6,4,5,2,3,1},
{6,5,2,3,4,1},
{6,2,3,4,5,1},
{2,1,3,6,5,4},
{2,3,6,5,1,4},
{2,6,5,1,3,4},
{2,5,1,3,6,4},
{4,5,6,3,1,2},
{4,6,3,1,5,2},
{4,3,1,5,6,2},
{4,1,5,6,3,2},
{3,1,4,6,2,5},
{3,4,6,2,1,5},
{3,6,2,1,4,5},
{3,2,1,4,6,5},
{5,2,6,4,1,3},
{5,6,4,1,2,3},
{5,4,1,2,6,3},
{5,1,2,6,4,3},
};

/*******
void rotatez(string &s)
{ char ch = s[1]; s[1]=s[2]; s[2]=s[3]; s[3]=s[4]; s[4]=ch; }

void rotatex(string &s)
{ char ch = s[0]; s[0]=s[1]; s[1]=s[5]; s[5]=s[3]; s[3]=ch; }

void rotatey(string &s)
{ char ch = s[0]; s[0]=s[2]; s[2]=s[5]; s[5]=s[4]; s[4]=ch; }
*********/
void solve()
{
    string s; cin >> s;
    sort(s.begin(), s.end());
    set<string> seen;
    int ans=0;
    do {
        string c = s;
        string cmin=s;
        // apply the 24 rotations in matrix
        /*
        for(int dz=0; dz<4; ++dz) {
            rotatez(c);
            for(int dx=0; dx<4; ++dx) {
                rotatex(c);
                for(int dy=0; dy<4; ++dy) {
                    rotatey(c);
                    chmin(cmin,c);
                }
            }
        }
        */
        for(int i=0; i<24; ++i)
        {
            for(int j=0; j<6; ++j) c[matrix[i][j]-1]=s[j];
            chmin(cmin,c);
        }
        if (seen.find(cmin)==seen.end())
        { seen.insert(cmin); ++ans; }
        //cout << cmin << endl;
    } while(next_permutation(s.begin(), s.end()));
    cout << ans << endl;
}

int main()
{
    solve();
}
