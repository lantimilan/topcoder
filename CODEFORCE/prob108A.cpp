// =========================================================
// 
//       Filename:  prob108A.cpp
// 
//    Description:  http://codeforces.com/contest/108/problem/A
// 
//        Version:  1.0
//        Created:  09/16/2011 10:02:14 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    string s; cin >> s;
    int hh=(s[0]-'0')*10 + (s[1]-'0');
    int mm=(s[3]-'0')*10 + (s[4]-'0');

    int h, m;
    for(h=m=0; ; ++m)
    {
        if (m>=60) { m=0; h++; }
        if (h>hh || (h==hh && m>mm))
        {
            if (h/10==m%10 && h%10==m/10)
                break;
        }
    }
    if (h>=24) { h=m=0; }
    printf("%02d:%02d\n",h,m);
}
