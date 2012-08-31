// =========================================================
//
//       Filename:  prob138B.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  12/26/2011 10:57:03 AM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/26/2011, LI YAN
//
// =========================================================
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100000+5;
char buf[MAXN];

int bestcnt, zero, aa, bb;

int main()
{
    gets(buf);
    int cnt[10]={0};

    int n=strlen(buf);
    for(int i=0; i<n; ++i) {
        cnt[buf[i]-'0']++;
    }
    int xx[10], yy[10];
    bestcnt=cnt[0];
    //for(int z=0; z<=cnt[0]; ++z)
    // no need to check all possible trailing zeros
    // it is always better to use 0 to pair 9 if there
    // exists some pair to make 10
    // note 0 cannot be used to make 10
    // and to make 9 you need only one 0
    for(int a=1; a<10; ++a)
    for(int b=1; b<10; ++b) 
    if (cnt[a] && cnt[b] && a+b==10)
    {    
        memcpy(xx, cnt, sizeof cnt);
        memcpy(yy, cnt, sizeof cnt);        
        //xx[0]-=z; yy[0]-=z;
        xx[a]--;  yy[b]--;
        //int curr = z + 1;
        int curr=1;
        int nine=0; // greedy get as many 9 as possible
        for(int d1=0; d1<10; ++d1)
        {
            int cc = min(xx[d1], yy[9-d1]);
            xx[d1]-=cc; yy[9-d1]-=cc;
            nine += cc;
        }
        int z = min(xx[0], yy[0]);
        curr += nine + z;
        if (curr > bestcnt) {
            bestcnt = curr; //zero = z; 
            zero = z;
            aa=a; bb=b;
        }
    }
    //printf("best %d, zero %d, a %d, b %d\n", 
    //    bestcnt, zero, aa, bb);
    char ans[2][MAXN];
    memcpy(xx, cnt, sizeof cnt);
    memcpy(yy, cnt, sizeof cnt);
    xx[0]-=zero; yy[0]-=zero;
    int p;
    for(p=0; p<zero; ++p) ans[0][p] = ans[1][p] = '0'; // trailing zero block
    if (aa+bb==10) { // ten then a block of nine
        xx[aa]--; yy[bb]--;
        ans[0][p]=aa+'0'; ans[1][p]=bb+'0'; ++p;
        for(int d1=0; d1<10; ++d1)
        {
            int d2=9-d1;
            int cc=min(xx[d1], yy[d2]);
            xx[d1]-=cc; yy[d2]-=cc;
            for(int i=0; i<cc; ++i) {
                ans[0][p]=d1+'0';
                ans[1][p]=d2+'0';
                ++p;
            }
        }
    }
    // process remain digits
    for(int d1=0, d2=0; d1<10 && d2<10; )
    {
        if (xx[d1]==0) { d1++; continue; }
        if (yy[d2]==0) { d2++; continue; }
        xx[d1]--; yy[d2]--;
        ans[0][p]=d1+'0';
        ans[1][p]=d2+'0';
        ++p;        
    }
    ans[0][p]=ans[1][p]='\0';
    reverse(ans[0], ans[0]+n);
    reverse(ans[1], ans[1]+n);
    puts(ans[0]); puts(ans[1]);
}
