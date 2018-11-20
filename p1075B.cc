// p1075B.cc
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> all(n+m);
    vector<int> drivers, riders;
    for (int i = 0; i < n+m; ++i) cin >> all[i];
    for (int i = 0; i < n+m; ++i) {
        int t; cin >> t;
        if (t == 1) {
            drivers.push_back(all[i]);
        } else {
            riders.push_back(all[i]);
        }
    }
    assert(drivers.size() == m);

    vector<int> ans(m);
    for (int d = 0, r = 0; r < riders.size(); ++r) {
        // find the driver before and after riders[r]
        int rpos = riders[r];
        while (d < drivers.size() && drivers[d] < rpos) d++;
        if (d == 0) ans[d]++;
        else if (d >= drivers.size()) ans[d-1]++;
        else {  // check d-1 and d
            int x1 = rpos - drivers[d-1];
            int x2 = drivers[d] - rpos;
            if (x1 > x2) ans[d]++;
            else ans[d-1]++;
        }
    }
    for (int d = 0; d < drivers.size(); ++d) {
        if (d > 0) cout << ' ';
        cout << ans[d];
    }
    cout << endl;
}
