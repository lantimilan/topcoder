// =========================================================
// 
//       Filename:  task.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/09/2012 08:03:25 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/09/2012, LI YAN
// 
// =========================================================

// partition into blocks of size sqrt(N)
// O(N*sqrt(N))
//
// Task Scheduling  C++     
// Submission Accepted
// 10/10 testcases passed
// 30 Point(s)
//  View Submission     Processed   2012-01-09 16:31 UTC
//
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;

const int MIN=-10000000;

struct task_t {
    int m; // machine process time
    int d; // deadline
    int x; // index
    task_t() { m=d=x=0; }
    task_t(int mm, int dd, int xx) { m=mm; d=dd; x=xx; }
};

bool operator<(task_t t1, task_t t2)
{
    if (t1.d < t2.d) return true;
    else return false;
}

void chmax(int &a, int b)
{
    if (a<b) a=b;
}

int main()
{
    int N; scanf("%d", &N);
    vector<task_t> tasks(N);
    map<int,int> lookup;
    for(int i=0; i<N; ++i) {
        scanf("%d%d", &tasks[i].d, &tasks[i].m);
        tasks[i].x = i;
    }
    sort(tasks.begin(), tasks.end());
    for(int i=0; i<N; ++i) {
        lookup[tasks[i].x] = i;
    }

    int B=int(sqrt(N)+1.0e-8);
    int NB=(N+B-1)/B;
    //printf("B %d NB %d\n", B, NB);
    int delay[1000], offset[1000]={0};
    for(int i=0; i<1000; ++i) delay[i]=MIN;

    for(int t=0; t<N; ++t) {
        int pos = lookup[t];
        int block = pos/B;
        int elapse=0;
        int maxdelay=MIN;
        for(int p=0; p<B; ++p) {
            int id=block*B+p;
            if (id>=N) continue;
            if (tasks[id].x <= t) {
                elapse += tasks[id].m;
                chmax(maxdelay, elapse-tasks[id].d);
            }
        }
        //printf("delay %d\n", maxdelay);
        chmax(delay[block], maxdelay);
        for(int b=block+1; b<NB; ++b) {
            offset[b]+=tasks[pos].m;
        }
        int ans=MIN;
        for(int b=0; b<NB; ++b) {
            int curr = offset[b]+delay[b];
            chmax(ans, curr);
        }
        if (ans < 0) ans=0;
        printf("%d\n", ans);
    }
}
