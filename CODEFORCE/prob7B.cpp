// =========================================================
// 
//       Filename:  prob7B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/19/2011 08:34:10 PM
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

void solve()
{
    int t, m; cin >> t >> m;
    VI cache(m,0);
    int var=1;

    for(;t>0;--t)
    {
        string cmd; cin >> cmd;
        if (cmd=="defragment") {
            int i,j;
            for(i=0,j=0; i<m && j<m; ++i)       
            { if (cache[i]) cache[j++]=cache[i]; }
            for(; j<m; ++j) cache[j]=0;
        }
        else if (cmd=="alloc") {
            bool success=false;
            int nbytes; cin >> nbytes;
            for(int i=0; i+nbytes<=m; ++i) if (cache[i]==0) {
                bool vacant=true;
                for(int j=0; j<nbytes; ++j) if (cache[i+j])
                { vacant=false; break; }
                if (vacant) { 
                    for(int j=0; j<nbytes; ++j) cache[i+j]=var; 
                    success=true; break; 
                }
            }
            if (success) { cout << var << endl; ++var; }
            else { cout << "NULL" << endl; }
        }
        else {
            int id; cin >> id;
            if (id<=0) { cout << "ILLEGAL_ERASE_ARGUMENT" << endl; continue; }
            bool found = false;
            for(int i=0; i<m; ++i) if (cache[i]==id) { found=true; cache[i]=0; }
            if (found) {}
            else { cout << "ILLEGAL_ERASE_ARGUMENT" << endl; }
        }
    }
}

int main()
{
    solve();
}
