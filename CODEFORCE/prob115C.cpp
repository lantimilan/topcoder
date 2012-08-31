// =========================================================
// 
//       Filename:  prob115C.cpp
// 
//    Description:  http://codeforces.com/contest/115/problem/C
// 
//        Version:  1.0
//        Created:  09/15/2011 08:55:13 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD=1000000+3;

int mypow(int n)
{
    int ans=1;
    for(int i=0; i<n; ++i)
    {
        ans=(long long)ans*2 % MOD;
    }
    return ans;
}

int main()
{
    int n,m; cin >> n >> m;
    vector<string> grid(n);
    for(int i=0; i<n; ++i) cin >> grid[i];

    int cnt=0;
    // check rows
    for(int i=0; i<n; ++i)
    {
        int good=0, bad=0;
        {// left: (1,2) (3,4)
            for(int j=0; j<m; ++j)
            {
                if (j%2==0) { 
                    if (grid[i][j]=='1' || grid[i][j]=='2' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
                else {
                    if (grid[i][j]=='3' || grid[i][j]=='4' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
            }
        }
        {// right: (3,4) (1,2)
            for(int j=0; j<m; ++j)
            {
                if (j%2==0) { 
                    if (grid[i][j]=='3' || grid[i][j]=='4' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
                else {
                    if (grid[i][j]=='1' || grid[i][j]=='2' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
            }
        }
        good=2-bad;
        if (good==0) { cnt=-1; break; }
        if (good==2) cnt++;
    }
    if (cnt<0) { cout << 0 << endl; return 0; }

    // check cols
    for(int j=0; j<m; ++j)
    {
        int good=0, bad=0;
        { // top: (1,4) (2,3)
            for(int i=0; i<n; ++i)
            {
                if (i%2==0) {
                    if (grid[i][j]=='1' || grid[i][j]=='4' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
                else {
                    if (grid[i][j]=='2' || grid[i][j]=='3' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
            }
        }
        { // bottom: (2,3) (1,4)
            for(int i=0; i<n; ++i)
            {
                if (i%2==0) {
                    if (grid[i][j]=='2' || grid[i][j]=='3' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
                else {
                    if (grid[i][j]=='1' || grid[i][j]=='4' || grid[i][j]=='.') {}
                    else { bad++; break; }
                }
            }
        }
        good=2-bad;
        if (good==0) { cnt=-1; break; }
        if (good==2) cnt++;
    }
    if (cnt<0) cout << 0 << endl;
    else cout << mypow(cnt) << endl;
}

// 703933   Sep 16, 2011 8:22:32 AM     lantimilan  C - Plumber     GNU C++
// Accepted     640 ms  15100 KB 
