// =========================================================
// 
//       Filename:  prob219A.cpp
// 
//    Description:  http://codeforces.com/contest/219/problem/A
// 
//        Version:  1.0
//        Created:  08/30/2012 07:43:54 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/30/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int cnt[30];

int main()
{
    int k; cin >> k;
    string s; cin >> s;
    int n = s.size();
    for(int i=0; i<n; ++i)
        cnt[s[i]-'a']++;
    for(int i=0; i<26; ++i)
        if (cnt[i]%k) {
            cout << -1 << endl;
            return 0;
        }
    string ans;
    for(int i=0; i<26; ++i) {
        int m = cnt[i]/k;
        ans += string(m, char('a'+i));
    }
    string res;
    for(int i=0; i<k; ++i)
        res += ans;
    cout << res << endl;
}
