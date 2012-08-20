// =========================================================
// 
//       Filename:  equations.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/08/2012 04:03:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/08/2012, LI YAN
// 
// =========================================================

// ans is the number of factors of (N!)^2
//
// Submission Accepted
// 15/15 testcases passed
// 45 Point(s) 
//
#include <cassert>
#include <cstdio>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

const int MOD=1000000+7;
const int NN=1000000, RR=1000;

bool isprime[NN+5];
int cnt[NN+5];

vector<pii> table[RR+5];
int hit[RR+5];

int add(int a, int b)
{
    int c = int(((long long)a + b)%MOD);
    return c;
}

int sub(int a, int b)
{
    int c = a-b; if (c<0) c+=MOD;
    return c;
}

int mult(int a, int b)
{
    int c = int((long long)a * b %MOD);
    return c;
}

void init()
{
    isprime[0]=isprime[1]=false; 
    isprime[2]=isprime[3]=true;
    for(int i=4; i<= NN; ++i) {
        if (i%2==0 || i%3==0) isprime[i]=false;
        else isprime[i]=true;
    }
    for(int i=4; i<= NN; ++i) if (isprime[i]) {
        for(int j=2; j*j<=i; j++) if (i%j==0) {
            isprime[i]=false; 
            break;
        }
    }

    //for(int p=2; p<=100; ++p) if (isprime[p]) printf("%d ", p); 
    //putchar('\n');

    // seems not worth it for this table
    /*
    for(int i=2; i<= RR; ++i) {
        if (isprime[i]) table[i].push_back(pii(i,1));
        else {
            int p;
            for(p=2; p*p<=i && i%p!=0; ++p) {}

           assert(isprime[p] && p*p<=i);
           table[i]=table[i/p];
           bool dup=false;
           for(int x=0; x<int(table[i].size()); ++x) {
               if (table[i][x].first==p) { 
                   table[i][x].second++; dup=true; 
                   break;
               }
           }
           if (!dup) table[i].push_back(pii(p,1));
        }
    }
    */

    /*
    for(int i=2; i<=10; ++i) {
        printf("%d: ", i);
        for(int x=0; x<int(table[i].size()); ++x)
            printf("  p %d c %d  ", table[i][x].first, table[i][x].second );
        putchar('\n');
    }
    */
}

int main()
{
    init();
    int N; scanf("%d", &N);
    int ans=1;
    /*
    for(int p=2; p<= N; ++p) {
        if (isprime[p]) { cnt[p]++; continue; }
        int t=p;
        for(int q=2; q*q<=p; ++q) if (isprime[q] && t%q==0) {
            while(t>RR && t%q==0) {
                cnt[q]++; t/=q;
            }
            if (t<=RR) { hit[t]++; break; }
        }
    }
    for(int p=2; p<=RR; ++p) {
        for(int x=0; x<int(table[p].size()); ++x) {
            int prime=table[p][x].first, kk=table[p][x].second;
            cnt[prime] = add(cnt[prime], mult(kk,hit[p]));
        }
    }  */
    for(int p=2; p<=N; ++p) {
        if (isprime[p]) cnt[p]++;
        else {
            int t=p;
            while(t>1 && !isprime[t]) {
                for(int q=2; q*q<=t; ++q) if (t%q==0) {
                    while(t%q==0) { t/=q; cnt[q]++; }
                    break;
                }
            }
            if (t>1) { assert(isprime[t]); cnt[t]++; }
        }
    }
    for(int p=2; p<=N; ++p) if (isprime[p]) {
        //printf("p %d cnt %d\n", p, cnt[p]);
        ans = mult(ans, 2*cnt[p]+1);
    }
    printf("%d\n", ans);
}

// testcase
//
// 32327
// 656502
//
// 40921
// 686720
//
// 1000000
// 986406
//
// for((i=1; i<=10; ++i)); do  echo $i | ./a.out ; done
// 1
// 3
// 9
// 21
// 63
// 135
// 405
// 675
// 1215
// 2295
//
