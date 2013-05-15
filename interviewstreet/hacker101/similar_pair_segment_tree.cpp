// similar_pair.cpp

#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, T;
long long ans;

bool isroot[100000+5];

vector<int> tree[100000+5];

struct TreeNode {
    int l, r;
    int sum;
};

TreeNode segment_tree[(1<<17)*2+5];

void create(int x, int l, int r)
{
//cout << "create " << x << ' ' << l << ' ' << r << endl;
    assert(l < r);
    segment_tree[x].l = l;
    segment_tree[x].r = r;
    segment_tree[x].sum = 0;

    if (l+1 >= r) return;
    int m = (l+r) / 2;
    create(2*x+1, l, m);
    create(2*x+2, m, r);
}

void init()
{
    create(0, 0, n);
}

void add(int index, int val)
{
    int x = 0, l = 0, r = n;
    while (l+1 < r) {
        segment_tree[x].sum += val;
        int m = (l+r)/2;
        if (index < m) { x = 2*x + 1; r = m; }
        else { x = 2*x + 2; l = m; }
    }
    segment_tree[x].sum += val;
}

long long count(int l, int r, int x)
{
//cout << "count " << l << ' ' << r << ' ' << x << endl;
    int l1 = segment_tree[x].l;
    int r1 = segment_tree[x].r;
    assert(l < r && l1 < r1);
    if (r <= l1 || r1 <= l) return 0;
    if (l <= l1 && r1 <= r) return segment_tree[x].sum;
    long long s1, s2;
    s1 = count(l, r, 2*x+1);
    s2 = count(l, r, 2*x+2);
    return s1 + s2;
}

void dfs(int root)
{
//cout << "dfs " << root << endl;
    ans += count(root-T, root+T+1, 0);
    add(root, +1);
    for (int x = 0; x < tree[root].size(); ++x) {
        int child = tree[root][x];
        dfs(child);
    }
    add(root, -1);
}

int main()
{
    ans = 0;
    cin >> n >> T;
    init();

    for (int i = 0; i < n; ++i) isroot[i] = 1;

    for (int i = 0; i < n-1; ++i) {
        int a, b; cin >> a >> b;
        a--; b--;
        tree[a].push_back(b);
        isroot[b] = false;
    }
    int root = -1;
    for (int i = 0; i < n; ++i) if (isroot[i]) {
        root = i; break;
    }
    //cout << root << endl;
    dfs(root);
    cout << ans << endl;
}

// segment tree version

