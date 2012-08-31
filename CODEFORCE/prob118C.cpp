// =========================================================
// 
//       Filename:  prob118C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/07/2011 02:42:04 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/07/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    char in[10000+10], out[10000+10];
    int n, k; scanf("%d%d",&n,&k);
    scanf("%s",in);
    //printf("%d %d %s\n",n,k,in);

    int best=100000;
    out[0]='9'+1; out[1]='\0';
    for(char ch='0'; ch<='9'; ++ch)
    {
        char tmp[10000+10]; strcpy(tmp,in);
        int cost=0;
        int cnt=0;
        for(int i=0; i<n; ++i) cnt+=(tmp[i]==ch);
        if (cnt>=k) goto done;
        for(int d=1; d<=9; d++)
        {
            char c2;
            c2=ch+d;
            if ('0'<=c2 && c2<='9') {
                for(int i=0;i<n; ++i) {
                    if (tmp[i]==c2) { cost+=d; cnt++; tmp[i]=ch; }
                    if (cnt==k) { goto done; }
                }
            }
            c2=ch-d; 
            if ('0'<=c2 && c2<='9') {
                for(int i=n-1; i>=0; --i) {
                    if (tmp[i]==c2) { cost+=d; cnt++; tmp[i]=ch; }
                    if (cnt==k) { goto done; }
                }
            }
        }
        done:
        //printf("%s %d %d\n", tmp,cost,k);
        assert(cnt>=k);
        if (cost < best || (cost==best && strcmp(tmp,out)<0))
        { best=cost; strcpy(out,tmp); }
    }
    printf("%d\n",best);
    puts(out);
}

// 749212   Oct 8, 2011 4:12:23 AM  lantimilan  C - Fancy Number    GNU C++
// Accepted     30 ms   1400 KB
// 749201   Oct 8, 2011 4:08:21 AM  lantimilan  C - Fancy Number    GNU C++
// Wrong answer on test 10  30 ms   1400 KB
// 749194   Oct 8, 2011 4:06:33 AM  lantimilan  C - Fancy Number    GNU C++
// Wrong answer on test 8   30 ms   1400 KB
// 749190   Oct 8, 2011 4:05:01 AM  lantimilan  C - Fancy Number    GNU C++
// Wrong answer on test 6   30 ms   1400 KB
// 749188   Oct 8, 2011 4:03:35 AM  lantimilan  C - Fancy Number    GNU C++
// Runtime error on test 6  10 ms   1400 KB
// 749176   Oct 8, 2011 3:57:24 AM  lantimilan  C - Fancy Number    GNU C++
// Wrong answer on test 5   10 ms   1400 KB
