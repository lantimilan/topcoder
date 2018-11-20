// O(N^2) solution
#include <iostream>
#include <cassert>
using namespace std;

const int INF = 1e8;
int A[1000000+5];

bool match(int pos, int target) {
    return A[pos] == target || A[pos] < 0;
}

// A[l..r) must be a seq with A[pos] being a known value
bool match_seq(int pos, int l, int r, int* last = nullptr) {
    int anchor_val = (A[pos] > 0) ? A[pos] : 1;
    for (int k = pos, v = anchor_val; k >= l; --k, --v) {
        if (v < 1) return false;
        if (!match(k, v)) return false;
    }
    for (int k = pos, v = anchor_val; k < r; ++k, ++v) {
        if (!match(k, v)) return false;
        if (last) *last = v;
    }
    return true;
}

bool is_one_seq(int size) {
    int known_pos;
    for (known_pos = 0; known_pos < size; ++known_pos) {
        if (A[known_pos] > 0) break;
    }
    if (known_pos >= size) return true;
    return match_seq(known_pos, 0, size);
}

bool partial(int size, int* period) {
    *period = 0;
    for (int first = 0; first < size; ++first) {
        if (match(first, 1)) {  // l .. p 1 2 3 ... r, must have r <= l
            if (match_seq(first, first, size)) {
                int known_pos;
                for (known_pos = 0; known_pos < first; ++known_pos) {
                    if (A[known_pos] > 0) { break; }
                }
                if (known_pos >= first) { *period = INF; return true; }
                int currp;
                if (match_seq(known_pos, 0, first, &currp)) {
                    *period = max(*period, currp);
                }
            }
        }
    }
    return *period > 0;
}

bool check(int size, int period, int start) {
    // to the left of start, must be p, p-1, ...
    // to the right of start (inclusive), must be 1, 2, 3, ...
    for (int i = start - 1, k = period; i >= 0; --i, --k) {
        if (k < 1) return false;
        if (!match(i, k)) return false;
    }

    for (int i = start, k = 1; i < size; ++i, ++k) {
        if (k > period) k = 1;
        if (!match(i, k)) return false;
    }
    return true;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        // cout << "testcase:\n";
        for (int i = 0; i < N; ++i) {
         cin >> A[i];
         // cout << A[i] << endl;
        }
        int pmax = 0;
        if (is_one_seq(N)) { pmax = INF; }
        else if (partial(N, &pmax)) { /* do nothing, pamx already set */ }
        else {  // A[0..N) contains one full period
        for (int p = 1; p <= N; ++p) {
            for (int s = 0; s < N-1; ++s) {  // pos with 1
                if (check(N, p, s)) pmax = p;
            }
        }
        }
        if (pmax == 0) cout << "impossible" << endl;
        else if (pmax < INF) cout << pmax << endl;
        else cout << "inf" << endl;
    }
}
