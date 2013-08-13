// LELEMON.cpp

// sort bottles in each room max to min
// get the first k[i] bottles

#include <algorithm>
#include <iostream>
#include <cstring>
#include <functional>
using namespace std;


void solve()
{
    int n, m; cin >> n >> m;
    int k[105] = {0};
    for (int i = 0; i < m; ++i) {
        int room; cin >> room;
        k[room]++;
    }
    int bottles[105][105];
    int cnt[105] = {0};
    for (int i = 0; i < n; ++i) {
        cin >> cnt[i];
        for (int j = 0; j < cnt[i]; ++j)
            cin >> bottles[i][j];
        sort(bottles[i], bottles[i]+cnt[i], greater<int>());
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < min(cnt[i], k[i]); ++j) {
            ans += bottles[i][j];
        }
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--)
        solve();
}
