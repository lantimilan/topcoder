// =========================================================
// 
//       Filename:  luckyswap.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/23/2012 02:14:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/23/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAX=100000+5;
char str[MAX];
int c4[MAX], c7[MAX], b4[MAX], b7[MAX];
int max4, max7, now4, now7;

void solve()
{
    gets(str);
    max4=max7=now4=now7=0;
    memset(c4, 0, sizeof c4); // count of 4 in [0..pos-1]
    memset(c7, 0, sizeof c7); // count of 7 in [0..pos-1]
    memset(b4, 0, sizeof b4); // max interval [l..r] in [0..pos] for c4-c7
    memset(b7, 0, sizeof b7); // max interval [l..r] in [0..pos] for c7-c4

    int n=strlen(str);
    for(int pos=1; pos<=n; ++pos) {
        c4[pos]=c4[pos-1]; c7[pos]=c7[pos-1];
        if (str[pos-1]=='4') {
            c4[pos]++;
            now4++;
            max4=max(max4, now4);
            now7--;
            if (now7<0) now7=0;
        }
        else {
            c7[pos]++;
            now7++;
            max7=max(max7, now7);
            now4--;
            if (now4<0) now4=0;
        }
        b4[pos]=max4; b7[pos]=max7;
    }
    //printf("%d %d\n", b4[n], b7[n]);
    int ans=max(c4[n], c7[n]);
    for(int pos=1; pos<=n; ++pos) {
        int curr = c7[n]-c7[pos] + c4[pos]; // last 4 at pos-1
        curr += b7[pos-1];
        ans=max(ans, curr);
    }
    printf("%d\n", ans);
}

int main()
{
    int T; scanf("%d ", &T);
    while(T--) solve();
}

// lantimilan   4.2M    1.35    C++ 4.3.2   View Solution
