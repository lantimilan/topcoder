// =========================================================
// 
//       Filename:  Cslow.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/19/2012 01:53:41 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/19/2012, LI YAN
// 
// =========================================================


#include <cstdio>
#include <set>
using namespace std;

typedef long long int64;
set<int64> vals;

//const int MOD=1000000000+7;
int64 K, MOD;
const int MAX=10000000+3;
int ans[MAX];

void init()
{
    ans[0]=0; ans[1]=1;
    int64 sum=1; 
    vals.insert(2); vals.insert(3);
    for(int i=2; i<MAX; ++i) {
        set<int64>::iterator it=vals.begin();
        int64 a = *it;
        vals.insert(2*a); vals.insert(3*a);
        vals.erase(it);
        //printf("%lld ", a);
        sum = (sum+a)%MOD;
        ans[i]=sum;
    }
}

int main()
{
    scanf("%lld%lld", &K, &MOD);
    init();
    int sum;
    if (K<MAX) sum=ans[K];
    else {
        for(int i=MAX; i<K; ++i) {
        set<int64>::iterator it=vals.begin();
        int64 a = *it;
        vals.insert(2*a); vals.insert(3*a);
        vals.erase(it);
        sum = (sum+a)%MOD;
        }
    }
    printf("%d\n", int(sum%MOD));
}
