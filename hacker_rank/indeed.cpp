#include <iostream>
using namespace std;

typedef long long int64;
struct Node {
    int l, r;
    int64 extra;
    int size;
};

Node nodes[2000000+5];

int get_left(int id) {
    return id * 2 + 1;
}

int get_right(int id) {
    return id * 2 + 2;
}

int64 get_elem(int nodeid, int pos, int extra) {
    Node &node = nodes[nodeid];
    if (node.l + 1 == node.r){
        return node.extra + extra;
    } else {
        int s = node.r - node.l;
        if (pos < node.l + s/2) {
            return get_elem(get_left(nodeid), pos, extra + node.extra);
        } else {
            return get_elem(get_right(nodeid), pos, extra + node.extra);
        }
    }
}

void incr(int nodeid, int begin, int end, int extra) {
    Node &node = nodes[nodeid];
    if (begin <= node.l && node.r <= end) {
        node.extra += extra;
    } else if (begin >= node.r || end <= node.l) {
        // do nothing
    } else {
        incr(get_left(nodeid), begin, end, extra);
        incr(get_right(nodeid), begin, end, extra);
    }
}

void push(int nodeid, int64 val) {
    Node &node = nodes[nodeid];
    if (node.l + 1 >= node.r) {  // leaf
        node.extra = val;
    } else {
        int lchild = get_left(nodeid);
        int rchild = get_right(nodeid);
        incr(lchild, node.l, node.l + node.size, node.extra);
        incr(rchild, node.l, node.l + node.size, node.extra);
        node.extra = 0;
        node.size++;
        if (node.size <= (node.r - node.l) / 2) {
            push(lchild, val);
        } else {
            push(rchild, val);
        }
    }
}

void pop(int nodeid) {
    Node &node = nodes[nodeid];
    if (node.l + 1 >= node.r) {
        node.extra = 0;
    } else {
        if (node.size <= (node.r - node.l)/2) {
            pop(get_left(nodeid));
        } else {
            pop(get_right(nodeid));
        }
        node.size--;
    }
}

void create(int nodeid, int l, int r) {
    //cout << nodeid << ' ' << l << ' ' << r << endl;
    nodes[nodeid].l = l;
    nodes[nodeid].r = r;
    if (l+1 >= r) return;
    int m = l + (r-l)/2;
    create(get_left(nodeid), l, m);
    create(get_right(nodeid), m, r);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int M = 500000;
    create(0, 0, M);
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        string op; cin >> op;
        if (op == "push") {
            int64 val; cin >> val;
            push(0, val);
        } else if (op == "pop") {
            pop(0);
        } else {
            int k, extra; cin >> k >> extra;
            incr(0, 0, k, extra);
        }
        if (nodes[0].size == 0) {
            cout << "EMPTY" << endl;
        } else {
            int64 ans = get_elem(0, nodes[0].size-1, 0);
            cout << ans << endl;
        }
    }
    return 0;
}
