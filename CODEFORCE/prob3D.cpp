// =========================================================
// 
//       Filename:  prob3D.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/11/2011 10:32:18 PM
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
    string expr; cin >> expr;
    VI va, vb;
    int a,b;
    while(cin >> a >> b) { va.PB(a); vb.PB(b); }

    priority_queue<PII> diff;
    for(int p=0,i=0; p<sz(expr); ++p) if (expr[p]=='?')
    { diff.push(PII(va[i]-vb[i],p)); ++i; }

    int left, right, newleft, newright, other;
    left=right=newleft=newright=other=0;
    for(int p=0; p<sz(expr); ++p) {
        left += (expr[p]=='(');
        right += (expr[p]==')');
        other += (expr[p]=='?');
    }
    if (abs(left-right) > other) { cout << -1 << endl; return; }
    newleft = (other-(left-right))/2;
    newright = other-newleft;
    string curr = expr;
    int cnt=0;
    while(cnt<newright) {
        PII node = diff.top(); diff.pop();
        int pos = node.second; curr[pos]=')';
        ++cnt;
    }
    for(int p=0; p<sz(curr); ++p) if (curr[p]=='?') curr[p]='(';

    //cout << curr << endl;

    bool good = true;
    priority_queue<PII> used;

    int p=0,x=0;
    cnt=0;
    while(1) {
        for(; p<sz(curr); ++p) {
            if (expr[p]=='?') {
                if (curr[p]==')') used.push(PII(vb[x]-va[x],p));
                ++x;
            }
            if (curr[p]=='(') cnt++;
            else cnt--;
            if (cnt <0) break;
        }
        if (cnt>=0) break;
        if (used.empty()) { good=false; break; }
        int pos = used.top().second; used.pop(); curr[pos] = '('; 
        int spos=-1;
        while(!diff.empty()) 
        { spos = diff.top().second; diff.pop(); if (spos>=p) break; }
//cout << spos << " " << pos << endl;
        if (spos<p) { good=false; break; }
        curr[spos] = ')';
        //cout << curr << endl;
        cnt=1; ++p;
    }
    if (good) {
        LL score=0; int k=0;
        for(int p=0; p<sz(expr); ++p) if (expr[p]=='?')
        { if (curr[p]=='(') score += va[k]; else score += vb[k]; ++k; }
        cout << score << endl;
        cout << curr << endl;
    }
    else cout << -1 << endl;
}

int main()
{
    solve();
}
