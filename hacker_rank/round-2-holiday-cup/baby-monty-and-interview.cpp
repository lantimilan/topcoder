// baby-monty-and-interview.cpp
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

const int X = 10000;
int vis[X+5];
int parent[X+5];
int sum[X+5];  // number of pairs at even dist rooted at node
int even[X+5];  // number of proper descendants at even dist rooted at node
int odd[X+5];  // number of proper descendants at odd dist rooted at node
vector<int> tree[X+5];


void dfs(int start) {
    vis[start] = 1;
    for (int next : tree[start]) if (!vis[next]) {
        parent[next] = start;
        dfs(next);
    }
}

int pairsum(const vector<int> &v) {
    int s1 = 0, s2 = 0;
    for (int k : v) {
        s1 += k;
        s2 += k*k;
    }
    s1 *= s1;
    assert((s1 - s2) % 2 == 0);
    return (s1 - s2) / 2;
}

void calc(int root) {
    sum[root] = odd[root] = even[root] = 0;
    for (int next : tree[root]) if (next != parent[root]) {
        calc(next);
    }
    for (int next : tree[root]) if (next != parent[root]) {
        odd[root] += even[next] + 1;
        even[root] += odd[next];
        sum[root] += sum[next];
    }
    vector<int> oddvec, evenvec;
    for (int next : tree[root]) if (next != parent[root]) {
        oddvec.push_back(odd[next]);
        evenvec.push_back(even[next] + 1);
    }
    sum[root] += pairsum(oddvec) + pairsum(evenvec);
    /*
    for (int k1 = 0; k1 < tree[root].size(); ++k1) if (tree[root][k1] != parent[root])
    for (int k2 = k1+1; k2 < tree[root].size(); ++k2) if (tree[root][k2] != parent[root]) {
        int v1 = tree[root][k1];
        int v2 = tree[root][k2];
        sum[root] += odd[v1] * odd[v2] + (1+even[v1]) * (1+even[v2]);
    }
    */
    sum[root] += even[root];
    //cout << root << ' ' << sum[root] << ' ' << odd[root] << ' ' << even[root] << endl;
}

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) tree[i].clear();
    for (int i = 0; i < N-1; ++i) {
        int x, y; cin >> x >> y; --x; --y;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    memset(vis, 0, sizeof vis);
    memset(parent, -1, sizeof parent);
    memset(sum, 0, sizeof sum);
    memset(even, 0, sizeof even);
    memset(odd, 0, sizeof odd);

    dfs(0);
    calc(0);
    cout << sum[0] << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
