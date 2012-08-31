// =========================================================
// 
//       Filename:  prob74A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  04/15/2011 07:17:40 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <map>
#include <string>
using namespace std;

void solve()
{
    map<string,int> coders;
    int n; cin >> n;
    for(int i=0; i<n; ++i)
    {
        string name; cin >> name;
        int points[7];
        for(int k=0; k<7; ++k)
            cin >> points[k];
        coders[name] += points[0]*100;
        coders[name] -= points[1]*50;
        for(int k=2; k<7; ++k) coders[name] += points[k];
    }
    string bestcoder =coders.begin()->first;
    int bestscore = coders.begin()->second;
    map<string,int>::const_iterator cit;
    for(cit=coders.begin(); cit!=coders.end(); ++cit)
    { if (cit->second > bestscore)
        { bestcoder = cit->first; bestscore = cit->second; }
    }
    cout << bestcoder << endl;
}

int main()
{
    solve();
}
