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
        // how to count
        // 1. if group is even, for that group, k-1 * k-3 * ... * 1
        // 2. if group is odd, then single element has k choices
        // once we have identified odd elements, there is only one way to
        // pair them up
        for (int i = N-1; i >= 0; ) {
            int val = S[i];
            int k = 0; while (i >= 0 && S[i] == val) { ++k; --i; }
            if (k&1) { mult(ans, k--); }
            mult(ans, calc(k));
        }
        cout << ans << endl;
    }
}
