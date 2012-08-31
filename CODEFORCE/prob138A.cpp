// =========================================================
// 
//       Filename:  prob138A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  12/24/2011 09:16:08 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 12/24/2011, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
#include <cstring>
using namespace std;

const char *vowel="aeiou";

void getsuffix(const char *str, int k, char *suffix)
{
        int len = strlen(str);
        int nvow=0;
        for(int p=len-1, q=0; p>=0; --p, ++q) {
            char ch=str[p];
            suffix[q]=ch;
            if (strchr(vowel, ch)) nvow++;
            if (nvow==k) break;
        }
        if (nvow<k) suffix[0]='\0';
}

int main()
{
    int n, k; scanf("%d%d ", &n, &k); 
    //char dummy[10005];
    //gets(dummy);

    int ans=7; // 1, 10, 100, 111 in binary
    char line[4][10000];
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<4; ++j)
        {
            gets(line[j]); //puts(line[j]);
        }
        char suffix[4][10000];
        for(int j=0; j<4; ++j)
        {
            getsuffix(line[j], k, suffix[j]); 
            if (strlen(suffix[j]) == 0) { ans=0; goto done; }
        }
        int curr; // too many if/els, to improve
        if (strcmp(suffix[0], suffix[1]) == 0) {
            if (strcmp(suffix[2], suffix[3]) == 0) {
                if (strcmp(suffix[0], suffix[2]) == 0) curr=7;
                else curr=1;
            }
            else {
                curr = 0;
            }
        }
        else {
            if (strcmp(suffix[0], suffix[2]) == 0) {
                if (strcmp(suffix[1], suffix[3]) == 0) curr = 2;
                else curr=0;
            }
            else if (strcmp(suffix[0], suffix[3]) == 0) {
                if (strcmp(suffix[1], suffix[2]) == 0) curr = 4;
                else curr=0;
            }
            else curr=0;
        }
        ans &= curr;
    }
    done:
    switch(ans) {
    case 0: puts("NO");   break;
    case 1: puts("aabb"); break;
    case 2: puts("abab"); break;
    case 4: puts("abba"); break;
    case 7: puts("aaaa"); break;
    default: assert(false);
    }
}
