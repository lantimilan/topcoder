// stock-values.cpp
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void solve() {
    int N; cin >> N;
    int a[20];
    for (int i = 0; i < N; ++i) cin >> a[i];

    int best = 0;
    // msb is a[1]
    for (int m = (1<<N-2)-1; m >= 0; --m) {
        int mask = m << 1;
        int b[20];
        memcpy(b, a, sizeof b);
        bool good = true;
        int p;
        for (p = 1; p < N-1; ++p) if (1<<(N-1-p) & mask) {
            // no speed up if use bit &
            if (b[p-1] % 2 == 0 && b[p+1] % 2 == 0) {
                b[p] = (b[p-1] + b[p+1]) /2;
            } else {
                good = false;
                break;
            }
        }
        if (!good) {
            // keep only the highest p bits
            int s = N-2 - p;
            m &= ~((1 << s) -1);
            continue;
        }
        int sum = 0;
        for (int i = 0; i < N/2; ++i) {
            sum += abs(b[i] - b[N-1-i]);
        }
        best = max(best, sum);
    }
    cout << best << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
