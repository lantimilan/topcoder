// =========================================================
// 
//       Filename:  median.cpp
// 
//    Description:  Little Elephant and Median
//
//    Problem code: MEDIAN
// 
//        Version:  1.0
//        Created:  05/03/2012 08:55:36 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/03/2012, LI YAN
// 
// =========================================================

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <map>
#include <queue>
using namespace std;

map<int, int> dist;
void solve()
{
    dist.clear();
    int n; scanf("%d", &n);
    int a[40];
    for(int i=0; i<n; ++i) scanf("%d", a+i);

    int maxval=a[0];
    for(int i=1; i<n; ++i) maxval=max(maxval, a[i]);
    for(int i=0; i<n; ++i) if (a[i]==maxval) a[i]=1; else a[i]=0;

    int start=0;
    for(int i=0; i<n; ++i) start |= a[i]<<i;
    queue<int> que;
    que.push(start); dist[start]=0;
    while(!que.empty()) {
        start = que.front(); que.pop(); //printf("start %d\n", start);
        assert(dist.count(start));
        int p1, p2, diff, mindiff;
        for(p1=0, p2=-1; p1<n && p2<n; ) {
            diff=0; mindiff=100; // loop invariant, either p2+1=p1 or p1..p2 has diff=0
            for(int p=p2+1; p<n; ++p) { // look for farthest mindiff
                if (start & 1<<p) diff--; // get 1
                else diff++; // get 0
                if (diff <= mindiff || diff <=0) { mindiff=diff; p2=p; }
            }
            
            if (mindiff <0) { // reach a[n-1], done
                int cnt=p2-p1+1;
                int conf = start | ((1<<cnt)-1)<<p1;
                if (!dist.count(conf)) {
                    dist[conf]=dist[start]+1;
                    que.push(conf);
                }
                break;
            }
            else {
                if (mindiff>0) {
                    for(; p1<=p2 && mindiff>0; ++p1) {
                        if (start & 1<<p1) mindiff++; // skip 1
                        else mindiff--; // skip 0
                    }
                }
                //printf("p1 %d p2 %d mindiff %d\n", p1, p2, mindiff);
                if (mindiff<=0) {
                    assert(mindiff==0);
                    int cnt=p2-p1+1;
                    int conf = start | ((1<<cnt)-1)<<p1;
                    if (!dist.count(conf)) {
                        dist[conf]=dist[start]+1;
                        que.push(conf);
                    }
                }
                else break; // there is no 1 from p1 to n-1, we can stop
            }
        }
    }
    printf("%d\n", dist[(1<<n)-1]);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=1; t<=T; ++t) solve();
}

// 
//
// Correct Answer
// Execution Time: 0.02
//
//ID    Date    Problem     Result  Time    Mem     Lang    
//1049402     46 sec ago  Little Elephant and Median  
//    0.02    2.8M    C++ 4.3.2   View Solution
//1049386     16 min ago  Little Elephant and Median  
//    0.02    2.8M    C++ 4.3.2   View Solution
//1049383     18 min ago  Little Elephant and Median  
//    0.02    2.8M    C++ 4.3.2   View Solution
//1049253     4 hours ago     Little Elephant and Median  
//    0.00    2.8M    C++ 4.3.2   View Solution
//1049249     4 hours ago     Little Elephant and Median  
//    0.01    2.8M    C++ 4.3.2   View Solution
//1049244     5 hours ago     Little Elephant and Median  
//    0.02    2.9M    C++ 4.3.2   View Solution
//1049242     5 hours ago     Little Elephant and Median  
//    0.02    2.9M    C++ 4.3.2   View Solution
//1049196     8 hours ago     Little Elephant and Median  
//    -   7.3M    C++ 4.3.2   View Solution
//1048995     12 hours ago    Little Elephant and Median  
//    0.26    3.5M    C++ 4.3.2   View Solution
//1048890     14 hours ago    Little Elephant and Median  
//    -   7.3M    C++ 4.3.2   View Solution 
//
// this one needs O(n) to do transition from one state to
// next, and there are 2^30 possible states but not many
// of them are reachable, as each transition only get
// to state with more 1's
