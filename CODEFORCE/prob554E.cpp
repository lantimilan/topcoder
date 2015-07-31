// prob554E.cpp
//
// Analysis:
// Consider a[n]
// let subset S1 of a[1..n-1] be friends of a[n]
// and subset S2 of a[1..n-1] be enemies of a[n]
// then each pair in S1 must be friends
// and each pair in S2 must be friends
// and each a[i] in S1 and a[j] in S2 must be enemies
// So once the split is done, there is only one valid configuration
// Now use the edges, we build a graph with a collection of components
// each =1 and =0 edge would add nodes to a component, with
// =1 would add a node with the same label, =0 would add a node with different
// label. If a node receives two different labels, then ans = 0
// Suppose we have C components, ans = 2^C / 2 = 2^C-1 because every component
// can be into the first or second partition, and each partition occurs twice
// due to symmetry

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

const int MOD = 1e9+7;

vector<pair<int,int>> graph[100000+5];  // (neighbor, friend 1 or enemy 0)
int label[100000+5]; // 0 not seen, 1 left, 2 right
int N, M;

bool dfs(int start, int val) {
    if (label[start] != 0) {
        return label[start] == val;
    }
    label[start] = val;
    for (const auto& p : graph[start]) {
        int nb = p.first;
        int edge = p.second;
        if (edge == 0) {
            if (!dfs(nb, 3-val)) return false;
        } else {
            if (!dfs(nb, val)) return false;
        }
    }
    return true;
}

int pow2(int l) {
    int ans = 1;
    for (int i = 0; i < l; ++i) {
        ans = 1LL * ans * 2 % MOD;
    }
    return ans;
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }
    int ans = -1;
    int comp = 0;
    for (int i = 0; i < N; ++i) if (label[i] == 0) {
        comp++;
        if (!dfs(i, 1)) {
            ans = 0;
            break;
        }
    }
    if (ans < 0) ans = pow2(comp-1);

    cout << ans << endl;
}
