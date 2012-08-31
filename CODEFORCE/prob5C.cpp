// =========================================================
// 
//       Filename:  prob5C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/14/2011 02:22:27 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/14/2011, LI YAN
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
void chmax(T &a, T b) { a=(a>=b)?a:b; }

void solve()
{
    string expr; cin >> expr;
    int diff=0, curr=0, last=-1, begin, end;
    int ans=0, cnt=0;
    for(int i=0; i<sz(expr); )
    {
        // skip rparen
        while(i<sz(expr) && expr[i]==')') ++i;
        if (i>=sz(expr)) break;

        assert(expr[i]=='('); // begin a new segment
        diff = 0; 
        begin=i, end=i;
        while(1) {
            if (expr[i]=='(') diff++;
            else diff--;
            if (diff==0) { end=i; break; } 
            ++i; if (i>=sz(expr)) break;
        }
        if (end > begin) { 
            if (last>=0 && last+1 == begin) curr+=end-begin+1; // continue prev seg
            else curr = end-begin+1;
            if (ans < curr) { ans=curr; cnt=1; }
            else if (ans == curr) ++cnt;
            last = end;
        }
    }
    //cout << ans << ' ' << cnt << endl;
    if (diff > 0) { // search backwards for diff=0 since all diff >0 now
        last=-1; diff=0;
        int prev=end; //cout << "prev " << prev << endl;
        for(int i=sz(expr)-1; i>prev; )
        {
            while(i>prev && expr[i]=='(') --i;
            if (i<=prev) break;

            assert(expr[i]==')');
            begin=end=i;
            while(i>prev) { 
                if (expr[i]=='(') ++diff; else --diff;
                if (diff==0) { begin=i; break; }
                --i;
            }
            if (end > begin) {
                if (last>=0 && end+1==last) curr += end-begin+1;
                else curr = end-begin+1;
    
                if (ans < curr) { ans=curr; cnt=1; }
                else if (ans == curr) ++cnt;
    
                last=begin;
                //cout << curr << endl;
            }
        }
    }
    if (ans==0) cnt=1;
    cout << ans << ' ' << cnt << endl;
}

int main()
{
    solve();
}
