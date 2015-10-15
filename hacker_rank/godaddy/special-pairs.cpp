// special-pairs.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

// A biconnected component (bcc) is defined by a non-bridge edge and all edges
// in a common cycle are in this bcc.
//
// The standard way is to get all bridges, then build bcc starting with a non-
// bridge edge and collect all edges in the same bcc. This is because bcc
// form a partition of non-bridge edges.
//
// Definition: assume G is undirected and connected
//     articulation point v: the removal of v disconnects G
//     bridge e: the removal of e disconnects G
//     biconnected component bcc: e1 and e2 are in the same bcc iff they are in
// the same cycle.
//
// edge(p,v) is a bridge iff none of nodes in subtree(v) can reach p or its
// ancestor, that is low[v] >= discover[v]
//
// We know that a bcc is from some subtree, that is, they do not split in two
// different subtrees.
// Also, a bcc is rooted at either tree root, or an articulation point, because
// a non-articulation point has some descendant with a back edge going to
// parent or upper and would thus include its parent into this bcc.
//
// Algorithm bcc:
// for each node v
// if v is root or arti, then
// for each child c of v
// if edge(v,c) is not bridge
// then start from c to explore the subtree and include nodes that do not make
// their parent an articulation point, because they have some decendant with
// a back edge going to parent or above.
int N, M, Q;
int CC;
int BCC;
vector<set<int>> graph;
vector<set<int>> label;

int low[100000+5];
int vis[100000+5];
int discover[100000+5];
int parent[100000+5];
int arti[100000+5];

void chmin(int &x, int y) {
    if (x > y) x = y;
}

void dfs2(int first, int second) {
    label[first].insert(BCC);
    label[second].insert(BCC);
    for (int next : graph[second]) if (parent[next] == second) {
        if (low[next] < discover[second]) {
            // there is a back edge from subtree of next to second or above
            dfs2(second, next);
        }
    }
}

void dfs(int start) {
    vis[start] = 1;
    discover[start] = ++CC;
    low[start] = discover[start];
    for (int next : graph[start]) {
        if (!vis[next]) {
            parent[next] = start;
            dfs(next);
            if (low[next] >= discover[start]) { arti[start] = 1; }
            chmin(low[start], low[next]);
        } else if (next != parent[start]) { // back_edge, grandparent or beyond
            chmin(low[start], discover[next]);
        }
    }
    //cout << start << ' ' << low[start] << ' ' << arti[start] << endl;
}

void biconnected() {
    memset(vis, 0, sizeof vis);
    memset(parent, -1, sizeof parent);

    CC = 0;
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        dfs(i);
    }

    for (int i = 0; i < N; ++i) if (arti[i])
    for (int j : graph[i])  // build a bcc rooted at i and include j
    if (parent[j] == i && low[j] == discover[i]) {
        BCC++; //cout << i << ' ' << j << ' ' << BCC << endl;
        dfs2(i,j);
    }
}

bool intersect(const set<int> &s1, const set<int> &s2) {
    if (s1.size() < s2.size()) {
        for (int e : s1) {
            if (s2.count(e)) return true;
        }
    } else {
        for (int e : s2) {
            if (s1.count(e)) return true;
        }
    }
    return false;
}

int main() {
    cin >> N >> M >> Q;
    graph.resize(N); label.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        graph[u].insert(v);
        graph[v].insert(u);
    }
    biconnected();

    for (int i = 0; i < Q; ++i) {
        int u, v; cin >> u >> v; --u; --v;
        if (intersect(label[u], label[v])) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

// Accepted
// Improvement: label the bcc with some node so that we can quickly check
// whether two nodes were in the same bcc.
