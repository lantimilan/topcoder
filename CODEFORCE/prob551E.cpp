// prob551E.cpp
// Problem:
// Given an array A[n] with n at most 5x10^5, and q queres with q = 5x10^4.
// Each query is either (l, r, val), asking for the leftmost val in A[l..r]
// and rightmost val in A[l..r]
// or (l, r, incr), meaning add incr to each of A[i] in A[l..r]
//
// This is easy once you see answering each query in sqrt(N) is enough.
// So we make blocks of size 1000, and then we have at most 500 blocks.
// Each query can be answered by looking at partial blocks elements and full
// blocks. And each update works the same way.

#include <iostream>
#include <set>
using namespace std;

const int BSIZE = 1000;
int N, NBLOCKS;

typedef set<pair<long long, int>> ElemType;
struct Block {
    int l, r;
    ElemType elts;  // (val, pos)
    long long extra;

    int get_left(int l, int r, long long val);
    int get_right(int l, int r, long long val);
    void update(int l, int r, int incr);
    void print();
};

void Block::print() {
    cout << "block: " << l << " " << r << " " << extra << endl;
    for (const auto &p : elts) {
        cout << p.first << " : " << p.second << endl;
    }
}

// Return distance between leftmost val and rightmost val in the intersection
// of this block and A[l..r],
// or -1 if there is no val in the intersection
int Block::get_left(int l, int r, long long val) {
    long long target = val - extra;
    ElemType::iterator it = elts.lower_bound(make_pair(target, l));

    if (it->first != target) return -1;
    else return it->second;
}

int Block::get_right(int l, int r, long long val) {
    long long target = val - extra;
    ElemType::iterator it = elts.lower_bound(make_pair(target, r+1));
    if (it != elts.begin()) --it;
    if (it->first == target) return it->second;
    return -1;
}

// If A[l..r] covers full block, update extra by incr, else update the elts
// in A[l..r] by adding incr to them.
void Block::update(int l, int r, int incr) {
    if (l <= this->l && this->r <= r) {
        extra += incr;
    } else {
        ElemType newelts;
        for (const auto& p : elts) {
            long long newval = p.first;
            if (l <= p.second && p.second <= r) {
                newval += incr;
            }
            newelts.insert(make_pair(newval, p.second));
        }
        elts = newelts;
    }
}

Block blocks[505];

void process_update(int l, int r, int x) {
    int b1 = l / BSIZE;
    int b2 = r / BSIZE;
    for (int b = b1; b <= b2; ++b) {
        blocks[b].update(l, r, x);
    }
}

void chmin(int &a, int b) {
    if (b == -1) return;
    if (a == -1 || a > b) a = b;
}

void chmax(int &a, int b) {
    if (b == -1) return;
    if (a == -1 || a < b) a = b;
}

int process_query(int y) {
    int left = -1, right = -1;
    for (int b = 0; b < NBLOCKS; ++b) {
        int l = blocks[b].get_left(0, N-1, y); chmin(left, l);
        int r = blocks[b].get_right(0, N-1, y); chmax(right, r);
        //cout << "block " << b << ": " << l << " " << r << endl;
        //cout << left << ' ' << right << endl;;
    }
    if (left != -1) {
        return right - left;
    }
    return -1;
}

int main() {
    int n, q; cin >> n >> q; N = n;
    int nblocks = (n + BSIZE-1) / BSIZE; NBLOCKS = nblocks;
    for (int b = 0; b < nblocks; ++b) {
        int l = b * BSIZE;
        int r = l + BSIZE - 1;
        blocks[b].l = b * BSIZE;
        blocks[b].r = r;
        blocks[b].extra = 0;
    }
    for (int i = 0; i < n; ++i) {
        int v; cin >> v;
        int bindex = i / BSIZE;
        blocks[bindex].elts.insert(make_pair(v, i));
    }
    for (int i = 0; i < q; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int l, r, x; cin >> l >> r >> x;
            process_update(l-1, r-1, x);
        } else {
            int y; cin >> y;
            int ans = process_query(y);
            cout << ans << endl;
        }
        /*
        for (int b = 0; b < NBLOCKS; ++b) {
            blocks[b].print();
        }
        */
    }
}
