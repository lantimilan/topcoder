// =========================================================
// 
//       Filename:  CARVANS.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/23/2012 09:18:15 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/23/2012, LI YAN
// 
// =========================================================

#include <cstdio>
using namespace std;

int speed[10000+5];

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        int N; scanf("%d", &N);
        for(int i=0; i<N; ++i)
            scanf("%d", speed+i);

        int ans=1;
        int curr = speed[0];
        for(int i=1; i<N; ++i)
            if (speed[i] > curr) {}
            else {
                ans++;
                if (speed[i] < curr)
                    curr = speed[i];

            }
        printf("%d\n", ans);
    }
}
