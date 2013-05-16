// similar_pair.cpp

// use fenwick tree, also called binary indexed tree BIT
//
// let the itmes be a[0..n-1]
// then s[0..n] is
// s[0] = 0
// s[1] = a[0]
// s[2] = a[0..1]
// s[3] = a[2]
// s[4] = a[2..3]
// s[5] = a[4]
// s[6] = a[4..5]
// s[7] = a[6]
// s[8] = a[0..7]
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, T;
long long ans;

bool isroot[100000+5];
int a[100000+5];
int s[100000+5];

vector<int> tree[100000+5];


void add(int index, int val)
{
    int x = index;
    s[++x] += val;
    while (x <= n) {
//        x += (x & -x);  // add lsb, the right most 1, this one works
        x += ((x & x-1) ^ x);  // add lsb, the right most 1
        s[x] += val;
    }
}

long long count(int end)  // sum a[0..end-1]
{
    long long ans = 0;
    while (end != 0) {
        ans += s[end];
        end &= end - 1;
    }
    return ans;
}

long long count(int l, int r)  // sum a[l..r-1]
{
    return count(r) - count(l);
}

void dfs(int root)
{
//cout << "dfs " << root << endl;
    ans += count(max(0,root-T), min(n,root+T+1));
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

// fenwick tree version
// Accepted
