// =========================================================
// 
//       Filename:  lucky.cpp
// 
//    Description:  CHEFLUCK
// 
//        Version:  1.0
//        Created:  05/03/2012 04:18:52 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;


int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t) {
        int N; scanf("%d", &N);
        int ans=-1;
        for(int y=0; y<7; ++y) {
            if (N>=4*y && (N-4*y) % 7 == 0) {
                ans=N-4*y; break;
            }
        }
        printf("%d\n", ans);
    }
}
