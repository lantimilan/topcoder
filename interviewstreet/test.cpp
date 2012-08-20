// =========================================================
// 
//       Filename:  test.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/06/2012 08:39:06 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/06/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main()
{
    int n=-5;
    if (n&1)
        printf("%d.5\n", n/2);
    else
        printf("%d\n", n/2);
}
