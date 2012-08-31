// =========================================================
// 
//       Filename:  prob6B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/18/2011 12:23:57 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/18/2011, LI YAN
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

void solve()
{
    int n, m; cin >> n >> m; 
    string s; cin >> s;
    char ch = s[0];
    VS matrix;
    for(int r=0; r<n; ++r) {
        cin >> s; matrix.PB(s);
    }

    int color[30]={0};
    for(int r=0; r<n; ++r)
    for(int c=0; c<m; ++c) if (matrix[r][c]==ch)
    {
        int dr[]={-1,0,+1,0};
        int dc[]={0,+1,0,-1};
        for(int x=0; x<4; ++x)
        {
            int rr=r+dr[x], cc=c+dc[x];
            if (0<=rr && rr<n && 0<=cc && cc<m)
                color[matrix[rr][cc]-'A']=1;
        }
    }
    int ans=0;
    for(int i=0; i<26; ++i) if (char(i+'A')!=ch)
        ans+=color[i];

    cout << ans << endl;
}

int main()
{
    solve();
}
