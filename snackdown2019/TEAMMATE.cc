#include <iostream>
#include <algorithm>
using namespace std;

const int MOD = 1e9+7;
int S[100000+5];

void mult(int& base, int amt) {
    base = 1LL * base * amt % MOD;
}

int calc(int n) {
    int ans = 1;
    for (int k = n-1; k >= 1; k-=2) {
        int d = k;
        ans = 1LL * ans * d % MOD;
    }
    return ans;
}

int main() {
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int i = 0 ; i < N; ++i) cin >> S[i];
        sort(S, S+N);
        int ans = 1;
        // how to count, two cases
        // case 1. previous highest is done
        // 1. if group is even, for that group, k-1 * k-3 * ... * 1
        // 2. if group is odd, then single element has k choices
        // case 2. previous highest has one element to be paired
        // 1. if group is even, then we pick one for previous and one for next
        // 2. if group is odd, then we just pick one for previous
        bool matched = true;
        for (int i = N-1; i >= 0; ) {
            int val = S[i];
            int k = 0; while (i >= 0 && S[i] == val) { ++k; --i; }
            if (matched) {
                if (k&1) {
                    // cout << "matched odd " << k << endl;
                    mult(ans, k);
                    mult(ans, calc(k-1));
                    matched = false;
                } else {
                    // cout << "matched even " << k << endl;
                    mult(ans, calc(k));
                    matched = true;
                }
            } else {  // one element from previous round unmatched
                if (k&1) {
                    // cout << "unmatched odd " << k << endl;
                    mult(ans, k);
                    mult(ans, calc(k-1));
                    matched = true;
                } else {
                    // cout << "unmatched even " << k << endl;
                    mult(ans, k);  // for previous highest
                    mult(ans, k-1);  // for next highest
                    mult(ans, calc(k-2));
                    matched = false;
                }
            }
        }
        cout << ans << endl;
    }
}
