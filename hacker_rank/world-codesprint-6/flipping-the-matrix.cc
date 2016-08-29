// flipping-the-matrix.cc
#include <iostream>
using namespace std;

// we can get max of each element from the 4 possible choices
int mat[256][256];

int calc(int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
        int d[4];
        d[0] = mat[i][j];
        d[1] = mat[i][2*n-1-j];
        d[2] = mat[2*n-1-i][j];
        d[3] = mat[2*n-1-i][2*n-1-j];
        int val = 0;
        for (int k = 0; k < 4; ++k) {
            val = max(val, d[k]);
        }
        sum += val;
    }
    return sum;
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < 2*n; ++i)
    for (int j = 0; j < 2*n; ++j) {
        cin >> mat[i][j];
    }
    cout << calc(n) << endl;
}

int main() {
    int q; cin >> q;
    while (q--) {
        solve();
    }
}

