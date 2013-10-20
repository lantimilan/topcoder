// prob338B.cpp

// given a tree, find all nodes that cover p[1..m] at a distance of d
// n = 10^5
//
// to check one node is easy, do a DFS

// solution:
// for each node t, the farthest marked node is either in subtree of t
// or outside subtree of t
// so for each node t, we first compute (max1, max2) where max1 is
// the dist from t to its farthest marked descendant (maybe t itself)
// and max2 is the dist from t to its second farthest marked descendant
// this can be done by dfs
// once we have that information, we do another dfs
// this time, we compute the dist from each node t to the farthest marked
// node that is outside subtree of t
// outside[] is computed by max of outside[parent]+1 and max of sibling + 1
// base case of tree root, outside[root] is 0 if tree root is marked, otherwise
// it is negative inf, meaning we are not going to use this value

#include <cstring>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int,int> pii;

const int INF = -1000000000;
const int N = 100000+5;
pii subtree[N];  // (max1, max2) the two max dist
bool marked[N];
int parent[N];  // parent[i] = j means j is parent of i
int outside[N];  // max dist from a node t to any marked node outside subtree(t)
bool vis[N];

int n, m, d;

vector< vector<int> > graph;

// return max dist from root to a marked descendant
// also set up subtree[root]
int dfs_subtree(int root)
{
    vis[root] = true;

    pii &p = subtree[root]; p.first = p.second = INF;
    if (marked[root]) p.first = 0;
    for (int x = 0; x < graph[root].size(); ++x) {
        int child = graph[root][x];
        if (!vis[child]) {
            parent[child] = root;
            int dd = dfs_subtree(child) + 1;
            if (dd > p.first) {
                p.second = p.first; p.first = dd;
            } else if (dd > p.second) {
                p.second = dd;
            }
        }
    }
    return subtree[root].first;
}

void dfs_outer(int root)
{
    vis[root] = true;
    for (int x = 0; x < graph[root].size(); ++x) {
        int child = graph[root][x];
        if (!vis[child]) {  // outside[child] either from sibling or parent
            //cout << "parent " << root+1 << " child " << child+1 << endl;
            int d1 = subtree[root].first;
            int d2 = subtree[root].second;
            int &target = outside[child];
            target = outside[root]+1;
            if (subtree[child].first+1 == d1) target = max(target, d2+1);
            else target = max(target, d1+1);
            dfs_outer(child);
        }
    }
}

int main()
{
    cin >> n >> m >> d;
    memset(marked, 0, sizeof marked);
    memset(parent, -1, sizeof parent);
    for (int i = 0; i < m; ++i) {
        int node; cin >> node; --node;
        marked[node] = true;
    }
    graph.resize(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        --a; --b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int root = 0;
    memset(vis, 0, sizeof vis);
    dfs_subtree(root);
    memset(vis, 0, sizeof vis);
    outside[root] = INF;
    dfs_outer(root);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int d1 = subtree[i].first;
        int d2 = outside[i];
        //cout << (i+1) << ' ' << d1 << ' ' << d2 << endl;
        if (max(d1,d2) <= d) { ans++; }
    }
    cout << ans << endl;
}

// Accepted
