// =========================================================
// 
//       Filename:  prob133A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/04/2011 08:53:45 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/04/2011, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstring>
using namespace std;

char line[128];

int main()
{
    gets(line);
    int n=strlen(line);
    for(int i=0; i<n; ++i)
    {
        if (line[i]=='H' || line[i]=='Q' || line[i]=='9')
        {
            puts("YES"); return 0;
        }
    }
    puts("NO");
}
