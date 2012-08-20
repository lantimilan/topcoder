// =========================================================
// 
//       Filename:  luckybal.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/20/2012 10:16:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/20/2012, LI YAN
// 
// =========================================================

// the only str that is not balanced is 777777, all 7's

#include <iostream>
#include <string>
using namespace std;

typedef long long int64;

string str; 

void solve()
{
    getline(cin, str); //cout << str << endl;
    int64 n = str.length();
    int64 ans = n*(n+1)/2; //cout << "ans " << ans << endl;

    // exclude all substr with all 7
    for(int i=0; i<n; ) 
    {
        if (str[i]=='4') { ++i; continue; }
        int j;
        for(j=i; j<n && str[j]=='7'; ++j) ;
        int64 sub=j-i;
        sub = sub*(sub+1)/2; //cout << "sub " << sub << endl;
        ans -= sub;
        i=j;
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T; cin.ignore(1024, '\n');
    while(T--) solve();
}
