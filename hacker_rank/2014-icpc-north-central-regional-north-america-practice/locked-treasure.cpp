// locked-treasure.cpp
#include <iostream>
using namespace std;

int comb[35][35];

void init() {
    comb[0][0] = 1;
    for (int n = 1; n <= 30; ++n) {
        comb[n][0] = 1;
        for (int r = 1; r <= n; ++r) {
            comb[n][r] = comb[n-1][r] + comb[n-1][r-1];
        }
    }
}

int main() {
    init();
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int n, k;
        cin >> n >> k;
        int r = n-k+1;
        cout << "Case " << t << ": ";
        cout << comb[n][r] << endl;
    }
}
