// =========================================================
// 
//       Filename:  prob137A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/15/2011 10:05:42 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/15/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;


int main()
{
    char buf[105];
    gets(buf); int n=strlen(buf);

    int cnt=0;
    for(int p=0; p<n; )
    {
        cnt++;
        int q=p;
        for(int k=0; k<5 && p+k<n; ++k)
            if (buf[p+k] != buf[p]) break;
            else q=p+k;
        p=q+1;
    }
    printf("%d\n", cnt);
}
