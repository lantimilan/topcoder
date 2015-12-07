// swapping-bridges.cpp
#include <cstring>
#include <iostream>
using namespace std;

int a[50000+5];
int vis[50000+5];

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> a[i]; a[i]--;
    }
    memset(vis, 0, sizeof vis);
    int comp = 0;
    for (int i = 0; i < N; ++i) if (!vis[i]) {
        comp++;
        int curr = i;
        do {
            vis[curr] = 1;
            curr = a[curr];
        } while (curr != i);
    }
    cout << comp-1 << endl;
}

int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
