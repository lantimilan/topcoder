// similar_pair.cpp

#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int n, T;

vector<vector<int> > tree;
vector<bool> isroot;

// find left most >= val
int lowersearch(int val, const vector<int> &vec)
{
    int n = vec.size();
    int lo = -1, hi = n;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (vec[mid] < val) lo = mid;
        else hi = mid;
    }
    return hi;
}

// find right most <= val
int uppersearch(int val, const vector<int> &vec)
{
    int n = vec.size();
    int lo = -1, hi = n;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (vec[mid] <= val) lo = mid;
        else hi = mid;
    }
    return lo;
}

pair<long long, vector<int> >
dfs(int root)
{
    long long ans = 0;
    priority_queue<int, vector<int>, greater<int> > pq;
    for (int i = 0; i < tree[root].size(); ++i) {
        pair<long long, vector<int> > p = dfs(tree[root][i]);
        ans += p.first;
        for (int i = 0; i < p.second.size(); ++i) pq.push(p.second[i]);
    }
    pq.push(root);
    vector<int> vec;
    while (!pq.empty()) {
        vec.push_back(pq.top());
        pq.pop();
    }
    //cout << root << ": " << vec[0] << ' ' << vec[vec.size()-1] << endl;
    int p1, p2;  // root - T <= vec[p1] and vec[p2] <= root + T
    p1 = lowersearch(root - T, vec);
    p2 = uppersearch(root + T, vec);
    ans += p2 - p1 + 1 - 1;
    return make_pair(ans, vec);
}

int main()
{
    cin >> n >> T;
    tree.resize(n);
    isroot.resize(n);
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
    pair<long long, vector<int> > p = dfs(root);
    long long ans = p.first;
    cout << ans << endl;
}

// seg fault
