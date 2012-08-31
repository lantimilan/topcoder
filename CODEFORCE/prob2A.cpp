// =========================================================
// 
//       Filename:  prob2A.cpp
// 
//    Description:  A. Winner
// 
//        Version:  1.0
//        Created:  03/15/2011 09:28:57 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/15/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<string,int> PSI;
typedef vector<int> VI;

#define fort(it,list) for(typeof list.begin() it=list.begin(); \
    it!=list.end(); ++it)

void solve()
{
    vector<PSI> data;
    map<string,int> total;

    int n; cin >> n;
    for(int i=0; i < n; ++i) { 
        string name; int score;
        cin >> name >> score; data.push_back(PSI(name,score));
        total[name] += score;
    }
    string winname; int winscore=0;
    fort(it,total) {
        int currscore = it->second;
        if (currscore > winscore) { winscore = currscore; }
    }

    map<string,int> recount;
    for(int i=0; i<n; ++i)
    {
        string name = data[i].first; int score = data[i].second;
        recount[name] += score; 
        if (total[name] == winscore && recount[name] >= winscore) 
        { winname=name; break; }
    }
    cout << winname << endl;
}

int main()
{
    solve();
}

/* **
 * 338231        Mar 16, 2011 8:16:50 AM    lantimilan        2A - Winner
 * GNU C++       Accepted        30 ms       1400 KB 
 *
 * 338230        Mar 16, 2011 8:11:34 AM    lantimilan        2A - Winner
 * GNU C++       Wrong answer on test 10     30 ms       1400 KB
 *
 * 338224        Mar 16, 2011 7:35:50 AM    lantimilan        2A - Winner
 * GNU C++       Wrong answer on test 10     30 ms       1400 KB 
 * */
