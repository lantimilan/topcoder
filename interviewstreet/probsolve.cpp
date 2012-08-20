// problem solving
//
// bipartite matching
// Hopcroft-Karp O(n^2.5)
//
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int N, K, NN;
int s, t;
int v[305];
int cap[700][700];
int from[700], to[700];
int dist[700];

bool dfs(int t)
{
    //printf("dfs %d\n", t);
    if (t<0) return true;
    for(int i=0; i<t-N; ++i) if (dist[i]>=0) {
        if (cap[i][t] && dist[i]==dist[t]-1) {
            int next = from[i];
            if (dfs(next)) { 
                from[i]=t; to[t]=i; dist[i]=dist[t]=-100;
                return true;
            }
        }
    }
    return false;
}

int augment(int round)
{
    memset(dist, -1, sizeof dist);
    int ans=0;
    // bfs to set up layer
    vector<int> dest;
    queue<int> que;
    for(int i=0; i<N; ++i) {
        if (from[i]<0) { que.push(i); dist[i]=0; }
    }
    int stop=500;
    while(!que.empty()) {
        int curr = que.front(); que.pop();
        int d=dist[curr]; if (d>stop) break; // the only optimization, cut bfs at first dist
        assert(d>=0);
        if (d%2==0) { // left to right, follor cap[][]
            for(int i=curr+1+N; i<2*N; ++i) if (cap[curr][i] && dist[i]<0) {
                dist[i]=d+1; que.push(i);
            }
        }
        else { // right to left, follow to[]
            int next = to[curr];
            if (next<0) { dest.push_back(curr); stop=d; }
            else { if (dist[next]<0) { dist[next]=d+1; que.push(next); } }
        }
    }

    // dfs to augment
    for(int i=0; i<int(dest.size()); ++i) {
        if (dfs(dest[i])) { ++ans; if (round*round >= N) return ans; } // still 5/10 with the if check
    }
    return ans;
}

void solve()
{    
    memset(cap, 0, sizeof cap);
    memset(from, -1, sizeof from);
    memset(to, -1, sizeof to);

    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i) scanf("%d", &v[i]);
    
    NN = 2*N;
    for(int i=0; i<N; ++i) {
        for(int j=i+1; j<N; ++j)
            if (abs(v[i]-v[j])>=K) cap[i][j+N]=1;
    }
    
    int ans=0;
    int incr=0;
    int round=0;
    while((incr=augment(round++))) { ans+=incr; }
    printf("%d\n", N-ans);
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t)
        solve();
}

// this is a bit strange, does the testcase become weaker?
//
// #    Status  Signal  Time
// 1    Passed  Success     0.298468
// 2    Passed  Success     0.435106
// 3    Passed  Success     0.394818
// 4    Passed  Success     0.425513
// 5    Passed  Success     0.4252
// 6    Passed  Success     0.414911
// 7    Passed  Success     0.495966
// 8    Passed  Success     0.495647
// 9    Passed  Success     0.37462
// 10   Passed  Success     0.435253
//
// cut search neighbor to half, passed 5 now
// Fri Jan  6 15:38:33 PST 2012
// Time Limit Exceeded
// 5/10 testcases passed
//
// Thu Jan  5 14:57:22 PST 2012
// Time Limit Exceeded
// 3/10 testcases passed
