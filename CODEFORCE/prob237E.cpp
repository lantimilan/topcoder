// =========================================================
// 
//       Filename:  prob237E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/25/2012 09:42:00 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/25/2012, LI YAN
// 
// =========================================================

// greedy

#include <cstdio>
#include <cstring>
using namespace std;

char str[105][105];
int cnt[105][30];
int avail[105];
char dest[105];
int hit[30];
int need[30];

int main()
{
    gets(dest);
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%s%d", str[i], &avail[i]);
    
    for(int i=0; i<n; ++i) {
        int len = strlen(str[i]);
        for(int j=0; j<len; ++j)
            cnt[i][str[i][j]-'a']++;
    }

    int len = strlen(dest);
    for(int i=0; i<len; ++i)
        need[dest[i]-'a']++;

    int cost = 0;
    for(int i=0; i<n; ++i) {
        for(int op=0; op<avail[i]; ++op) {
            for(char ch='a'; ch <= 'z'; ++ch) if (cnt[i][ch-'a'])
            { // use ch here
                if (hit[ch-'a'] < need[ch-'a']) {
                    cnt[i][ch-'a']--;
                    hit[ch-'a']++;
                    cost+=i;
                } else {
                
                }
            }
        }
    }
}
