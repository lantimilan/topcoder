// kth-zero.cc
// Given an array of n elements
// op=1 k, find pos of k-th zero, k is 1-based, pos is zero-based
// op=2 p x, a[p] = x, this could erase a zero
#include <cassert>
#include <iostream>
using namespace std;

namespace {
struct Node {
    int begin, end;
    int cnt;
    int left, right;
    Node() {
        cnt = 0;
        left = right = -1;
    }
};

int A[100000+5];
Node nodes[200000+5];
int C;

int create_node(int begin, int end) {
    int id = C;
    nodes[id].begin = begin;
    nodes[id].end = end;
    C++;
    if (begin + 1 >= end) {
        // do nothing
    } else {
        int n = (end - begin) / 2;
        int l = create_node(begin, begin+n);
        int r = create_node(begin+n, end);
        nodes[id].left = l;
        nodes[id].right = r;
    }
    return id;
}

void init(int n) {
    create_node(0, n);
}

void insert(int node, int pos, int val) {
    Node &curr = nodes[node];
    // cout << "insert " << curr.begin << ","
    //    << curr.end << "=>" << pos << " " << val << endl;
    if (curr.begin == pos && curr.end == pos+1) {
        if (val == 0) {
            curr.cnt = 1;
        } else {  // missed this base case
            curr.cnt = 0;
        }
    } else {
        if (A[pos] == 0 && val != 0) {
            curr.cnt--;
        }
        if (A[pos] != 0 && val == 0) {
            curr.cnt++;
        }
        int n = (curr.end - curr.begin) / 2;
        int lend = curr.begin + n;
        if (pos < lend) {
            insert(curr.left, pos, val);
        } else {
            insert(curr.right, pos, val);
        }
    }
}

int find(int node, int k) {
    Node curr = nodes[node];
    // cout << "find " << curr.begin << ' ' << curr.end << ' '
    // << curr.cnt << endl;
    if (curr.cnt < k) return -1;
    if (curr.begin + 1 >= curr.end) {
        assert(curr.cnt == 1 && k == 1);
        return curr.begin;
    }
    Node left = nodes[curr.left];
    if (left.cnt >= k) return find(curr.left, k);
    else return find(curr.right, k-left.cnt);
}

}  // unnamed namespace

int main() {
    int n, m; cin >> n >> m;
    init(n);
    for (int p = 0; p < n; ++p) {
        int val; cin >> val;
        A[p] = -1;
        insert(0, p, val);
        A[p] = val;
    }
    // cout << "query start:" << endl;
    for (int i = 0; i < m; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int k; cin >> k;
            // print k-th zero
            int pos = find(0, k);
            if (pos < 0) {
                cout << "NO" << endl;
            } else {
                cout << pos << endl;
            }
        } else {
            int p, x; cin >> p >> x; // cout << p << ' ' << x << endl;
            insert(0, p, x);
            A[p] = x;
        }
    }
}
