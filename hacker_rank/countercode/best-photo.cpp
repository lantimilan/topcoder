// best-photo.cpp
//
// If you draw a graph, with a[i]->a[j] if a[i] likes a[j]
// then you have n nodes and n edges, then the graph must be a collection of
// components with each component containing exactly one cycle with zero or
// more branches, and the external edge must point towards a cycle node,
// because a cycle node already has its next in cycle, the one that it liked.
// Now we can work on each component separately and the answer is the product
// of the individual components.
//
// For a copmonent, there are two cases:
// 1. all n node are in one cycle, then score = n-1, num = n because we can
// start at any node to form a line
// 2. at least one branch exists. then at least one of the cycle edge entering
// the tail of that branch cannot be used, because we can only use c-1 cycle
// edges, where c is the number of edges in cycle, using a branch edge would
// give use score + 1. So the cycle symmetry breaks.
// We can count by looking at each nodes with nonzero incoming edges.
// prod of indeg(node) for all such nodes.
// However, we could be counting a configuration with all cycle edges, and we
// have to exclude that one, and that is the only one we exclude.
//
// Accepted, worst time is 1.56s, time limit is 2s

#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
using namespace std;

const int M = 1000000;
const int MOD = 1e9+7;
set<int> graph[M+5];
vector<int> directed[M+5];
int indeg[M+5];
int vis[M+5];
int done[M+5];
int incycle[M+5];
vector<int> comp;
int C;
int unsatisfied;

int fact(int n) {
    int ans = 1;
    for (int i = 2; i <= n; ++i) ans = 1LL * ans * i % MOD;
    return ans;
}

void dfs2(int s) {
    vis[s] = 1; comp.push_back(s);
    for (int v : graph[s]) {
        if (!vis[v]) {
            dfs2(v);
        }
    }
}

// detect cycle nodes!
// because each node has exactly one outgoing edge in directed graph
// No forward edge
// No cross edge
// only tree edge and back edge are possible
void dfs(int s) {
    vis[s] = 1;
    for (int v : directed[s]) {
        if (!vis[v]) {
            dfs(v);
        } else {  // found cycle
            if (!done[v]) {
                int node = v;
                while (node != s) {
                    incycle[node] = 1; //cout << "node << " << node << endl;
                    node = directed[node].front();
                }
                assert(node == s);
                incycle[node] = 1;
            }
        }
    }
    done[s] = 1;
}

pair<int,int> process(int s) {
    comp.clear(); C++;
    dfs2(s);
    for (int v : comp) vis[v] = 0;
    for (int s : comp) if (!vis[s]) dfs(s);

    int ncomp = comp.size();
    int ncycle = 0;
    for (int v : comp) {
        ncycle += incycle[v];
    }
    if (ncycle == ncomp) {  // all nodes in this comp form a simple cycle
        int score = ncomp-1;
        int cnt = ncomp;
        unsatisfied++;
        return make_pair(score, cnt);
    } else {  // at least one branch
        int sat = 0;
        for (int v : comp) {
            sat += (indeg[v] >= 1);
        }
        int unsat = ncomp - sat; unsatisfied += unsat;
        int score = sat;
        int cnt = 1;
        for (int v : comp) {
            if (indeg[v]) cnt = 1LL * cnt * indeg[v] % MOD;
        }
        int bad = 1;
        for (int v : comp) {
            if (indeg[v] && !incycle[v]) bad = 1LL * bad * indeg[v] % MOD;
        }
        cnt -= bad; if (cnt < 0) cnt += MOD;
        return make_pair(score, cnt);
    }
}

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int u, v;
        u = i; cin >> v; --v;
        indeg[v]++;
        graph[u].insert(v);
        graph[v].insert(u);
        directed[u].push_back(v);
    }
    int score = 0;
    int cnt = 1;
    // break into components by ignore edge direction
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        // detect cycle and mark cycle node
        // count this component
        pair<int,int> p = process(i);
        score += p.first;
        cnt = 1LL * cnt * p.second % MOD;
    }
    cnt = 1LL * cnt * fact(unsatisfied) % MOD;
    cout << score << ' ' << cnt << endl;
}
