// =========================================================
// 
//       Filename:  prob187A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/10/2012 09:07:46 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/10/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

int a[200000+5];
int b[200000+5];
int rev[200000+5];
int arev[200000+5];
int used[200000+5];
int N;

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) { scanf("%d", &a[i]); --a[i]; }
    for(int i=0; i<N; ++i) { scanf("%d", &b[i]); --b[i]; }

    for(int i=0; i<N; ++i) rev[b[i]]=i;
    for(int i=0; i<N; ++i) arev[i] = rev[a[i]];
    for(int i=0; i<N; ++i) a[i] = arev[i];

    //for(int i=0; i<N; ++i) printf("%d ", a[i]); putchar('\n');

    int ans=0, target=N-1;
    int pos=N-1, next;
    while(target>0) {
        //printf("pos %d target %d\n", pos, target);
        for(next=pos; next>=0 && a[next] != target; --next) {
            used[a[next]]=1;
        }
        assert(next>=0);
        for(target--; target>=0 && used[target]; target--);
        ans+=pos-next;
        pos=next-1;
    }
    printf("%d\n", ans);
}
