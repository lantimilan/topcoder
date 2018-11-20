// CHEFKO.cc
//
// Correct Answer
// Execution Time: 0.35
// -------solution----------
// Note that segments are arranged in increasing lpoint and decreasing rpoint
// because a right-er rpoint is more useful than a left-er rpoint.
// And we only need to keep track of a minheap of rpoint with size K.
//
// ------original thoughts--------
// when we have pleft, and an event of rpoint comes,
// we need to remove seg_index from pleft, but then we also need to update
// maxlen, two cases:
// 1. if seg_index is smaller than Kth, then we have len = rpoint[seg_index]
// - lpoint[Kth]
// 2. if seg_index is larger than Kth, then we have len = rpoint[seg_index]
// - lpoint[seg_index]
//
// The hard part is to find Kth in stl set, or a RedBlack tree. How?
#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <queue>
#include <vector>
using namespace std;

vector<pair<int,int>> segments;
priority_queue<int> rpoints;  // key is -rpoint, so smaller key goes to top

bool compare(const pair<int,int>& p1, const pair<int,int>& p2) {
    if (p1.first != p2.first) {
        return p1.first < p2.first;
    } else {
        return p1.second > p2.second;
    }
}

void solve() {
    assert(rpoints.empty());
    int N, K; cin >> N >> K;
    segments.resize(N);
    for (int i = 0; i < N; ++i) {
        int l, r; cin >> l >> r;
        segments[i] = {l, r};
    }
    sort(segments.begin(), segments.end(), compare);

    int maxlen = 0;
    for (const auto& p : segments) {
        int l = p.first, r = p.second;
        // cout << "l,r " << l << ' ' << r << endl;
        rpoints.push(-r);
        if (rpoints.size() >= K) {
            int top = -rpoints.top();
            int len = top - l;
            maxlen = max(maxlen, len);
            // cout << "len,l,r " << len << ' ' << l << ' ' << r << endl;
            rpoints.pop();
        }
    }
    cout << maxlen << endl;
    while (!rpoints.empty()) rpoints.pop();
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
