// =========================================================
// 
//       Filename:  prob106A.cpp
// 
//    Description:  http://codeforces.com/contest/106/problem/A
// 
//        Version:  1.0
//        Created:  09/13/2011 08:30:13 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/13/2011, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int getrank(char ch)
{
    char rank[]="6789TJQKA";
    for(size_t i=0; i<sizeof(rank)/sizeof(rank[0]); ++i)
        if (ch==rank[i]) return i;
    return -1;
}
int main()
{
    char trump; scanf("%c",&trump);
    char c1[2], c2[2];
    scanf(" %c%c",&c1[0],&c1[1]);
    scanf(" %c%c",&c2[0],&c2[1]);

    bool beat=false;
    if (c1[1]==trump && c2[1]!=trump) { beat=true; }
    if (c1[1]==c2[1] && getrank(c1[0])>getrank(c2[0])) { beat=true; }

    if (beat) printf("YES\n");
    else printf("NO\n");
}
