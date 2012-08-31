// =========================================================
// 
//       Filename:  prob133C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/04/2011 09:27:45 PM
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

int rev(int k)
{
    int ans=0;
    for(int p=0; p<8; ++p)
    {
        ans = (ans<<1) | (k&1);
        k>>=1;
    }
    return ans;
}

int main()
{
    char line[128];
    gets(line);
    for(char *p=line; *p && *p!='\n'; ++p)
    {
        int prev=0;
        if (p>line) prev=*(p-1);
        int curr = (rev(prev)-rev((int)*p)) % 256;
        if (curr<0) curr+=256;
        printf("%d\n", curr);
        prev=curr;
    }
}
