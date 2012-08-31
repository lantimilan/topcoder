
// =========================================================
//
//       Filename:  prob137E.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  12/15/2011 10:54:15 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/15/2011, LI YAN
//
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

#define MAXN 300000
char str[MAXN+5];
int vow[MAXN+5], con[MAXN+5];
pii diff[MAXN+5];

const char *vowchar="AEIOUaeiou";


int main()
{
    gets(str);
    int n=strlen(str);
    int maxlen=0, maxcnt=0;

    for(int i=0; i<n; ++i) {
        if (i) { vow[i]=vow[i-1]; con[i]=con[i-1]; }

        if (strchr(vowchar, str[i])) { str[i]='0'; vow[i]++; } // vow is 0
        else { str[i]='1'; con[i]++; } // con is 1

        diff[i].first=vow[i]-2*con[i];
        diff[i].second=i;
    }

    sort(diff, diff+n);
    for(int i=0,j=1; i<n; i=j) {
        for(j=i+1; j<n && diff[j].first==diff[i].first; ++j)
            ;
        int currlen = diff[j-1].second - diff[i].second;
        maxlen=max(maxlen, currlen);
    }

    int nvow=0, ncon=0;
    for(int pos=0; pos<n; ++pos) {
        if (str[pos]=='0') nvow++;
        else ncon++;

        if (nvow <= 2*ncon) {
            maxlen = max(maxlen, pos+1);
        }
    }

    nvow=ncon=0;
    for(int pos=n-1; pos>=0; --pos) {
        if (str[pos]=='0') nvow++;
        else ncon++;
        if (nvow <= 2*ncon) {
            maxlen = max(maxlen, n-pos);
        }
    }

    if (maxlen) {
        int nvow=0, ncon=0;
        for(int i=0; i<maxlen; ++i) {
            if (str[i]=='0') nvow++;
            else ncon++;
        }
        if (nvow<=2*ncon) maxcnt++;
        for(int i=0,j=maxlen; i<n && j<n; ++i,++j) {
            if (str[i]=='0') nvow--; else ncon--;
            if (str[j]=='0') nvow++; else ncon++;

            if (nvow<=2*ncon) maxcnt++;
        }
        printf("%d %d\n", maxlen, maxcnt);
    }
    else puts("No solution");
}

// 967332   Dec 18, 2011 10:38:18 PM    lantimilan  E - Last Chance     GNU C++
// Accepted     60 ms   6300 KB
//
// should use pos+1 instead of pos, line 66: maxlen = max(maxlen, pos+1);
// 967327   Dec 18, 2011 10:35:49 PM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 53  60 ms   6300 KB
//
// O(n^2) algorithm for all submissions below
//
// 965070   Dec 17, 2011 11:39:08 AM    lantimilan  E - Last Chance     GNU C++
// Time limit exceeded on test 13   2000 ms     1600 KB
// 965060   Dec 17, 2011 11:33:44 AM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 12  30 ms   1600 KB
// 965048   Dec 17, 2011 11:24:40 AM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 11  30 ms   1600 KB
// 965036   Dec 17, 2011 11:17:23 AM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 3   30 ms   1600 KB
// 965026   Dec 17, 2011 11:13:28 AM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 1   10 ms   1600 KB
// 965019   Dec 17, 2011 11:11:32 AM    lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 1   30 ms   1600 KB
// 964771   Dec 17, 2011 5:55:25 AM     lantimilan  E - Last Chance     GNU C++
// Wrong answer on test 11  10 ms   1600 KB
// 964749   Dec 17, 2011 4:59:40 AM     lantimilan  E - Last Chance     GNU C++
// Time limit exceeded on test 13   2000 ms     1600 KB 
