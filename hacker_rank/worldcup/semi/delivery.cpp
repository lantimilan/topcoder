// delivery.cpp
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
using namespace std;

// break down to SCC and recursively construct a path
// each node in SCC can be ordered arbitrarily
//
// ACCEPTED

int N, M, K;
set<int> graph[100000+5];  // use set if detect duplicate
set<int> revgraph[100000+5];
int is_deliver[100000+5];
int compid[100000+5];
vector<int> postorder;

int CLOCK;
int COMP;
int TRACK;
int vis[100000+5];
int pre[100000+5];
int post[100000+5];
vector<vector<int>> comps;
vector<set<int>> comp_graph;
int comp_cnt[100000+5];  // count of delivery vertices in comp subtree
bool has_deliver[100000+5];
int child[100000+5];
int num_deliver[100000+5];
vector<int> path;
vector<int> ans;
vector<int> tmp;

vector<int> get_deliver(int comp) {
    vector<int> ans;
    for (int d : comps[comp]) if (is_deliver[d]) {
        ans.push_back(d);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// follow graph to set up pre/post
void dfs(int s) {
    vis[s] = 1; pre[s] = ++CLOCK;
    for (int next : graph[s]) if (!vis[next]) {
        dfs(next);
    }
    post[s] = ++CLOCK;
    postorder.push_back(s);
}

// follow revgraph
void dfs2(int s) {
    vis[s] = 1;
    compid[s] = COMP;
    comps[COMP].push_back(s);

    for (int next : revgraph[s]) if (!vis[next]) {
        dfs2(next);
    }
}

void scc() {
    CLOCK = 0; COMP = 0;
    comps.clear(); comp_graph.clear();

    memset(vis, 0, sizeof vis);
    for (int node = 0; node < N; ++node) if (!vis[node]) {
        dfs(node);
    }
    memset(vis, 0, sizeof vis);
    for (int i = N-1; i >= 0; --i) {
        int node = postorder[i];
        if (!vis[node]) {
            comps.push_back(vector<int>());
            dfs2(node);
            COMP++;
            assert(comps.size() == COMP);
        }
    }
}

void solve() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        graph[i].clear();
        revgraph[i].clear();
        is_deliver[i] = 0;
        compid[i] = -1;
    }
    postorder.clear();

    for (int i = 0; i < K; ++i) {
        int node; cin >> node; --node;
        is_deliver[node] = 1;
    }
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;  // can the same pair appear twice?
        --u; --v;
        graph[u].insert(v);
        revgraph[v].insert(u);
    }

    scc();

    // check comp
    /*
    for (int c = 0; c < COMP; ++c) {
        cout << "comp " << c << ": ";
        for (int node : comps[c]) {
            cout << node << ' ';
        }
        cout << endl;
    }
    */

    comp_graph.resize(COMP);
    for (int i = 0; i < N; ++i) {
        for (int j : graph[i]) {
            int c1 = compid[i], c2 = compid[j];
            assert(c1 >= 0 && c2 >= 0);
            if (c1 != c2) {
                comp_graph[c1].insert(c2);
            }
        }
    }
    /*
    cout << "comp_graph: ";
    for (int i = 0; i < COMP; ++i) {
        cout << "comp " << i << ": ";
        for (int d : comp_graph[i]) {
            cout << d << ' ';
        } cout << endl;
    }
    */

    memset(comp_cnt, 0, sizeof comp_cnt);
    for (int i = 0; i < N; ++i) {
        int c = compid[i];
        if (is_deliver[i]) comp_cnt[c]++;
    }

    memset(child, -1, sizeof child);
    for (int c = COMP-1; c >= 0; --c) {
        int ch = 0;
        for (int next : comp_graph[c]) {
            if (num_deliver[next] > ch) {
                ch = num_deliver[next];
                child[c] = next;
            }
        }
        num_deliver[c] = comp_cnt[c] + ch;
    }

    int start = -1;
    for (int c = 0; c < COMP; ++c) {
        if (num_deliver[c] == K) {
            start = c; break;
        }
    }

    if (start < 0) {
        cout << -1 << endl;
        return;
    }

    ans.clear();
    int node = start;
    while (node >= 0) {
        vector<int> curr = get_deliver(node);
        sort(curr.begin(), curr.end());
        copy(curr.begin(), curr.end(), back_inserter(ans));
        node = child[node];
    }

    for (int d : ans) {
        cout << (d+1) << ' ';
    }
    cout << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
