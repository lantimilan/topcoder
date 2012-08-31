// =========================================================
// 
//       Filename:  prob128B.cpp
// 
//    Description:  http://codeforces.com/contest/128/problem/B
// 
//        Version:  1.0
//        Created:  12/04/2011 07:45:39 PM
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

#define MAXN 100005
char str[MAXN];
int validPos[MAXN];

int main()
{
    gets(str);
    int index; scanf("%d",&index); --index;

//printf("%s %d\n", str, index);

    int n=strlen(str);
    if ((long long)n*(n+1)/2 <= index)
    {
        puts("No such line.");
        return 0;
    }
    int validLen=n;
    for(int i=0; i<validLen; ++i) validPos[i]=i;

    for(int length=0; length<n; ++length)
    for(char ch='a'; ch<='z'; ++ch)
    {
        long long sumLen=0LL;
        int cnt=0;
        int any=-1;
        int newLen=0;
        for(int i=0; i<validLen; ++i) {
            if (validPos[i]+length<n && str[validPos[i]+length]==ch) {
                any=validPos[i];
                cnt++;
                int len=n-validPos[i]-length;
                sumLen += len; //printf("found %lld %d\n", sumLen, len);
                newLen++;
            }
        }
        //printf("sumLen %lld index %d length %d\n", sumLen, index, length);
        if (sumLen > index) {
            if (cnt > index) { //printf("%d %d\n", any, length);
                char ans[MAXN]; strncpy(ans,str+any,length+1);
                puts(ans);
                return 0;
            }
            else {
                index -= cnt;
                int newpos=0;
                for(int i=0; i<validLen && newpos<newLen; ++i) {
                    if (validPos[i]+length<n && str[validPos[i]+length]==ch) {
                        validPos[newpos++]=validPos[i];
                    }
                }
                validLen=newLen; //printf("newLen %d\n", newLen);
                break; // continue to next length
            }
        }
        else {
            index-=sumLen; // continue to next ch
        }
    }
}
// 930544   Dec 5, 2011 8:42:14 AM  lantimilan  B - String  GNU C++     Accepted
// 30 ms    1900 KB 
//
// Egor's idea:
// build string from length=1,...,n
// try next char as 'a' to 'z'
// keep track of pos to extend substr
//
// 1. index-- to turn count into kth
// 2. validPos[] keep track of start of each valid substr
// 3. next char is at validPos[i]+length
// 4. we pay O(1) per substr and k<=10^5 so it is fast enough
