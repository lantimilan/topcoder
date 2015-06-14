// interval.cpp
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

struct Node {
    int l;
    int r;
    int minval;
    int minpos;
    Node *left;
    Node *right;
    Node(int ll, int rr, int mm, int pp) :
        l(ll), r(rr), minval(mm), minpos(pp), left(NULL), right(NULL) {}
};

const int INF = 1e6;
int N, Q;
int A[100000+5];
set<pii> ones;

void chmin(int &a, int b) {
    if (b < a) a = b;
}

Node *create(int l, int r) {
    Node *node = new Node(l, r, INF, INF);
    if (l+1 >= r) {
        return node;
    }
    int m = (l+r) / 2;
    Node *left = create(l, m);
    Node *right = create(m, r);
    node->left = left;
    node->right = right;
    return node;
}

void update(int pos, int val, Node *subtree) {
    //printf("update %d %d %p\n", pos, val, subtree);
    if (subtree == NULL) return;
    int l = subtree->l;
    int r = subtree->r;
    //printf("l %d r %d\n", l, r);
    if (pos < l || pos >= r) return;
    if (subtree->minval > val ||
        subtree->minval == val && subtree->minpos > pos) {
        subtree->minval = val;
        subtree->minpos = pos;
    }
    update(pos, val, subtree->left);
    update(pos, val, subtree->right);
}

int expand(int pos, int l, int r) {
    int x1, x2; x1 = pos; x2 = pos+1;
    set<pii>::iterator it = ones.lower_bound(pii(x1, x2));
    if (it != ones.end()) {
        if (it->first == x2) x2 = it->second;
    }
    if (it != ones.begin()) {
        --it;
        if (it->second == x1) x1 = it->first;
    }
    x1 = max(x1, l);
    x2 = min(x2, r);
    return x2 - x1;
}

pii query(int begin, int end, Node *subtree) {
    if (subtree == NULL) return pii(INF, INF);
    int l = subtree->l;
    int r = subtree->r;
    if (end <= l || begin >= r) return pii(INF, INF);
    if (begin <= l && r <= end) {
        return pii(subtree->minval, subtree->minpos);
    }
    pii p1 = query(begin, end, subtree->left);
    pii p2 = query(begin, end, subtree->right);

    int l1 = expand(p1.second, begin, end);
    int l2 = expand(p2.second, begin, end);

    if (p1.first < p2.first) return p1;
    if (p1.first == p2.first && l1 >= l2) return p1;
    return p2;
}

Node* init() {
    int l = -1;
    for (int i = 0; i < N; ++i) {
        if (A[i] == 1) {
            if (l < 0) l = i;
        } else {
            if (l >= 0) {
                ones.insert(pii(l, i));
                l = -1;
            }
        }
    }

    Node *root = create(0, N);
    for (int i = 0; i < N; ++i) {
        update(i, A[i], root);
    }
    return root;
}

void print(Node* root) {
    if (root == NULL) return;
    printf("%p %p %p %d %d %d %d\n", root, root->left, root->right,
        root->l, root->r, root->minval, root->minpos);
    print(root->left);
    print(root->right);
}

void solve() {
    for (int i = 0; i < Q; ++i) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int l, r; scanf("%d%d", &l, &r); --l; --r;
            int minval = A[l];
            for (int s = l; s <= r; ++s) chmin(minval, A[s]);

            if (minval == 0) {
                printf("%d %d %d\n", 0, l+1, r+1);
            } else {
                int len = 0; int ss, tt;
                for (int s = l; s <= r; ++s) if (A[s] == minval) {
                    int x1, x2;
                    for (x1 = s-1; x1 >= l && A[x1] == 1; --x1) ;
                    for (x2 = s+1; x2 <= r && A[x2] == 1; ++x2) ;
                    int newlen = x2 - x1 -1;
                    if (newlen > len || newlen == len && ss > x1 + 1) {
                        len = newlen;
                        ss = x1 + 1; tt = x2;
                    }
                    s = x2 -1;
                }
                printf("%d %d %d\n", minval, ss+1, tt);
            }
        } else {
            int l, v; scanf("%d%d", &l, &v); --l;
            A[l] = v;
        }
    }
}

int main() {
    cin >> N >> Q;
    for (int i = 0; i < N; ++i) cin >> A[i];

    if (1LL * N * Q <= 2e9) {
        solve();
        return 0;
    }

    Node *root = init(); //print(root);
    for (int i = 0; i < Q; ++i) {
        int op; scanf("%d", &op);
        if (op == 1) {
            int l, r; scanf("%d%d", &l, &r); --l; --r;
            pii p = query(l, r+1, root);
            int v = p.first;
            int x1, x2;
            if (v == 0) {
                x1 = l; x2 = r+1;
            // TODO: deal with minval = 1
            /*
            else if (v == 1) {
                assert(!ones.empty());
                set<pii>::iterator it = ones.lower_bound(pii(l, r+1));
                if (it == ones.end()) {
                    --it;
                    x1 = l+1; x2 = it->second;
                } else if (it->first <= l) {
                    x1 = l+1; x2 = r+1;
                } else {
                    if (it == ones.begin()) {
                        x1 = it->first + 1; x2 = r + 1;
                    } else {
                        set<pii>::iterator it2 = it;
                        --it2;
                        if (it2->second <= l) {
                            x1 = it->first + 1; x2 = r + 1;
                        } else {
                            x1 = l + 1; x2 = min(it2->second-1, r) + 1;
                        }
                    }
                }
            */
            } else {
                x1 = p.second; x2 = x1 + 1;
                if (!ones.empty()) {  // expand to left and right for ones
                    set<pii>::iterator it = ones.lower_bound(pii(x1, x2));
                    if (it != ones.end()) {
                        if (it->first <= x1) x2 = it->second;
                    }
                    if (it != ones.begin()) {
                        --it;
                        if (it->second >= x1) x1 = it->first;
                    }
                    x1 = max(x1, l);
                    x2 = min(x2, r+1);
                }
            }
            printf("%d %d %d\n", v, x1+1, x2);
        } else {
            int l, v; scanf("%d%d", &l, &v); --l;
            // update ones
            if (A[l] == 1 && v != 1) {
                set<pii>::iterator it = ones.lower_bound(pii(l,l+1));
                assert(it != ones.end());
                if (it->first <= l) {
                    pii seg = *it;
                    ones.erase(it);
                    if (seg.first < l) ones.insert(pii(seg.first, l));
                    if (l+1 < seg.second) ones.insert(pii(l+1, seg.second));
                } else {
                    if (it != ones.begin()) {
                        --it;
                        assert(it->first < l);
                        if (it->second > l) {
                            pii seg = *it;
                            ones.erase(it);
                            if (seg.first < l) ones.insert(pii(seg.first, l));
                            if (l+1 < seg.second) ones.insert(pii(l+1, seg.second));
                        }
                    }
                }
            }
            if (A[l] != 1 && v == 1) {
                int bb, ee; bb = l; ee = l+1;
                if (ones.empty()) {
                    ones.insert(pii(bb,ee));
                } else {
                    set<pii>::iterator it = ones.lower_bound(pii(l,l+1));
                    if (it->first == l+1) {  // merge with next
                        pii p = *it;
                        ones.erase(*it);
                        it = ones.insert(pii(l, p.second)).first;
                    }
                    if (it != ones.begin()) {  // merge with prev
                        set<pii>::iterator it2 = it;
                        --it2;
                        if (it2->second == it->first) {
                            bb = it2->first; ee = it->second;
                            ones.erase(it); ones.erase(it2);
                            ones.insert(pii(bb, ee));
                        }
                    }
                }
            }
            update(l, v, root);
            A[l] = v;
        }
    }
}
