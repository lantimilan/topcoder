// CHFAR.cc
#include <iostream>
using namespace std;

void solve() {
    int N, K; cin >> N >> K;
    int big = 0;
    for (int i = 0; i < N; ++i) {
        int element; cin >> element;
        big += (element > 1);
    }
    bool good = (big <= K);
    cout << (good ? "YES" : "NO") << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
