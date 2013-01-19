// TLE, maybe cin/cout too slow?
// not really, use binary search
//
// the key is to recognize the intervals with [1,i]
//
// [i,j] even means [1,i-1] eq [1,j]
// [i,j] odd means  [1,i-1] neq [1,j]
//
// disjoint set union
// maintain eq class
// non-eq edge implies bipartite graph

//#include <iostream>
#include <cassert>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

map<int,int> lookup;

const int MM = 5000*2;
int pa[MM+2];
int myrank[MM+2];
set<int> adj[MM+2];
int vis[MM+2];
int side[MM+2]; // 0 or 1, L or R
pii edge[MM+2];
pii inedge[MM/2 + 2];  // (i, j)
int inparity[MM/2 + 2];  // 0 or 1, even or odd
int E;
int N, K;

int myfind(int p)
{
    while (p != pa[p]) p = pa[p];
    return p;
}

bool dfs(int s, int parity)
{
    s = myfind(s);
    if (vis[s]) return true;
    vis[s] = 1;
    side[s] = parity;
    for (set<int>::iterator it = adj[s].begin();
        it != adj[s].end(); ++it) {
            int b = *it; b = myfind(b);
            if (!vis[b]) {
                bool good = dfs(b, 1-parity);
                if (!good) return false;
            }
            if (side[s] == side[b]) return false;
    }
    return true;
}

void solve()
{
    int i, j;
    int cnt = 0;
    int ans = -1;
    char par[10];
    int x, t, a, b;

    lookup.clear();
    // read input
    E = 0;
    for (x=0; x<K; ++x) {
        scanf("%d %d %s", &i, &j, par);
        int parity = (par[0] == 'o') ? 1 : 0;
        inedge[E] = pii(i,j);
        inparity[E] = parity;
        E++;
        if (!lookup.count(i-1)) lookup[i-1] = cnt++;
        if (!lookup.count(j)) lookup[j] = cnt++;
    }
    // binary search for best bound
    int lo = 0, hi = E+1;  // lo is valid, hi is invalid
    while (lo + 1 < hi) {
        int mid = (lo+hi)/2;
        bool good = true;
        // init
        for (x=0; x<cnt; ++x) { pa[x] = x; myrank[x] = 0; }
        // validate all endpoints
        for (x=0; x<mid; ++x) {
            i = inedge[x].first; j = inedge[x].second;
            if (i < 1 || j > N) { good = false; break; }
            assert(i <= j);
        }
        if (!good) { hi = x+1; continue; }
        // check eq class and bipartite of neq
        E = 0;
        for (x=0; x<mid; ++x) {
            i = inedge[x].first; j = inedge[x].second;
            --i;
            int a, b; a = lookup[i]; b = lookup[j];
            int p1, p2;
            if (inparity[x] == 1) {  // odd
                edge[E++] = pii(a,b);
            } else {  // even
                p1 = myfind(a); p2 = myfind(b);
                if (p1 != p2) {  // union by rank
                    if (myrank[p1] == myrank[p2]) {
                        pa[p2] = p1; myrank[p1]++;
                    } else if (myrank[p1] < myrank[p2]) {
                        pa[p1] = p2;
                    } else { pa[p2] = p1; }
                }
            }
        }
        // bipartite
        assert(good);
        for (t=0; t<cnt; ++t) { side[t] = -1; adj[t].clear(); vis[t] = 0; }
        for (t=0; t<E; ++t) {
            a = edge[t].first; b = edge[t].second;
            a = myfind(a); b = myfind(b);
            if (a==b) { good = false; break; }
            adj[a].insert(b); adj[b].insert(a);
        }
        if (good) good = dfs(0, 0);
        if (good) { lo = mid; }
        else { hi = mid; }
    }
    ans = lo;
    printf("%d\n", ans);
}

int main()
{
    while (scanf("%d", &N) == 1 && N >= 0) {
        scanf("%d", &K);
        solve();
    }
}

// 4729604  03:59:38  20 Jan 2013
// lantimilan  1003. Parity    C++ Accepted    0.156   1 460 KB
