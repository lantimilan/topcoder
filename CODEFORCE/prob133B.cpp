// =========================================================
// 
//       Filename:  prob133B.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/04/2011 08:57:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/04/2011, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;


int main()
{
    int map[512];
    map['>'] =  8;
    map['<'] =  9;
    map['+'] = 10;
    map['-'] = 11;
    map['.'] = 12;
    map[','] = 13;
    map['['] = 14;
    map[']'] = 15;

    char line[128];
    gets(line);
    const int factor=1<<4;
    const int MOD=1000000+3;
    long long ans=0LL;
    for(char *p=line; *p && *p!='\n'; ++p) 
    {
        ans = (ans*factor + map[*p])%MOD;
    }
    printf("%d\n", (int)ans);
}
