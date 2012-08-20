// kingdom.cpp
//
// Kingdom Connectivity(20 points)
//
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

typedef long long int64;
typedef set<int> si;
typedef pair<int,int> pii;

vector<si> from, backward;
map<pii,int> edgecnt;

const int MOD=1000000000;
int mark1[10000+5];
int mark2[10000+5];
int visit[10000+5];
int deg[10000+5];
int deg2[10000+5];
int dp[10000+5];

void refadd(int &a, int b)
{
    a = ((int64)a+b)%MOD;
}

int mult(int a, int b)
{
    return (int64)a*b%MOD;
}

void dfs(int v, const vector<si> &g, int m[])
{
    visit[v]=1; m[v]=1;
    for(si::iterator it=g[v].begin(); it!=g[v].end(); ++it)
    {
        if (!visit[*it]) dfs(*it, g, m);
    }
}

int main()
{
    int N, M; scanf("%d%d", &N, &M);
    from.resize(N);
    backward.resize(N);
    for(int i=0; i<M; ++i) {
        int a, b; scanf("%d%d", &a, &b);
        --a; --b;
        from[a].insert(b);
        backward[b].insert(a);
        edgecnt[pii(a,b)]++;
    }

    // mark all nodes on path from 0 to N-1
    mark1[0]=1;
    memset(visit, 0, sizeof visit);
    dfs(0,from,mark1);
    mark2[N-1]=1;
    memset(visit, 0, sizeof visit);
    dfs(N-1,backward,mark2);

    if (!mark1[N-1]) {
        puts("0"); return 0;
    }
    assert(mark2[0]);
    
    for(int i=0; i<N; ++i) if (mark1[i] && mark2[i]){
        for(si::iterator it=backward[i].begin(); it!=backward[i].end(); ++it) {
            if (mark1[*it] && mark2[*it]) deg[i]++;
            //if (*it == i) { puts("INFINITE PATHS"); return 0; }
        }
    }

    int ans=0;
    if (deg[0]) { ans=-1; }
    else {
        memcpy(deg2, deg, sizeof deg2);
        queue<int> que; que.push(0);
        while(!que.empty()) {
            int front = que.front(); que.pop();
            for(si::iterator it=from[front].begin(); it!=from[front].end(); ++it) {
                int k=*it;
                if (mark1[k] && mark2[k]) {
                    if (--deg2[k]==0) que.push(k);
                }
            }
        }
        if (deg2[N-1]>0) { ans=-1; }
        else {
            dp[0]=1;
            queue<int> que; que.push(0);
            while(!que.empty()) {
                int front = que.front(); que.pop();
                for(si::iterator it=backward[front].begin(); it!=backward[front].end(); ++it) {
                    int k=*it;
                    if (mark1[k] && mark2[k]) refadd(dp[front], mult(dp[k], edgecnt[pii(k,front)]));
                }
                for(si::iterator it=from[front].begin(); it!=from[front].end(); ++it) {
                    int k=*it;
                    if (mark1[k] && mark2[k]) {
                        if (--deg[k] == 0) que.push(k);
                    }
                }
            }
            ans = dp[N-1];
        }
    }
    if (ans<0) { puts("INFINITE PATHS"); }
    else { printf("%d\n", ans); }
}

// Kingdom Connectivity     cpp     2012-02-22 10:58:16     Processed   Accepted    View Details
//
// the bug is forgot to consider parallel edges
// Kingdom Connectivity     cpp     2012-02-20 10:20:01     Processed   Wrong Answer
// 2/10 testcases passed
//  View Details
//  Kingdom Connectivity    cpp     2012-02-20 08:39:16     Processed   Wrong Answer
//  2/10 testcases passed
//      View Details
