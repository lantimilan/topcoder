// =========================================================
// 
//       Filename:  Candies.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  07/13/2012 08:47:29 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 07/13/2012, LI YAN
// 
// =========================================================

// keep (rate, pos) and poping min rate
// if top has a neighbor assigned, then assign min val to qualify
//
//
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

class MyCmp {
public:
bool operator()(const pii &p1, const pii &p2) {
    if (p1.first != p2.first) return p1.first > p2.first;
    else return p1.second > p2.second;
}
};

typedef long long int64;
priority_queue<pii, vector<pii>, MyCmp> pq;

int N;
int rate[100000+5];
int candy[100000+5];

template<class T>
void chmax(T &a, const T &b)
{
    a=(a>b)?a:b;
}

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        int x; scanf("%d", &x);
        rate[i]=x;
        pq.push(pii(x,i));
    }
    int64 ans=0;
    while(!pq.empty()) {
        int rt, pos;
        rt   = pq.top().first;
        pos  = pq.top().second;
        pq.pop();
        candy[pos]=1;
        if (pos-1>=0) {
            int other = candy[pos-1];
            if (rate[pos-1]<rt) chmax(candy[pos], other+1);
        }
        if (pos+1<N) {
            int other = candy[pos+1];
            if (rate[pos+1]<rt) chmax(candy[pos], other+1);
        }
        ans += candy[pos];
    }
    printf("%lld\n", ans);
}


