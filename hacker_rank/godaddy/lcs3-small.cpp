// lcs3-small.cpp
#include <iostream>
using namespace std;

int N;
int s1[3005];
int s2[3005];
int s3[3005];
int lcs[501][501][501];
void chmax(int &x, int y) {
    if (x < y) x = y;
}

void solve() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> s1[i];
    for (int i = 0; i < N; ++i) cin >> s2[i];
    for (int i = 0; i < N; ++i) cin >> s3[i];

    for (int i1 = 0; i1 <= N; ++i1)
    for (int i2 = 0; i2 <= N; ++i2)
    for (int i3 = 0; i3 <= N; ++i3)
        lcs[i1][i2][i3] = 0;


    for (int l1 = 1; l1 <= N; ++l1)
    for (int l2 = 1; l2 <= N; ++l2)
    for (int l3 = 1; l3 <= N; ++l3) {
        if (s1[l1-1] == s2[l2-1] && s2[l2-1] == s3[l3-1]) {
            //cout << l1 << ' ' << l2 << ' ' << l3 << endl;
            lcs[l1][l2][l3] = lcs[l1-1][l2-1][l3-1] + 1;
        }
        chmax(lcs[l1][l2][l3], lcs[l1-1][l2][l3]);
        chmax(lcs[l1][l2][l3], lcs[l1][l2-1][l3]);
        chmax(lcs[l1][l2][l3], lcs[l1][l2][l3-1]);
    }

    cout << lcs[N][N][N] << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
