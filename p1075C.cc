// p1075C.cc
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Accepted
// If there is no vertical line, then there is a path, because horizontal lines
// do not merge, in other words, there is always gap between horizontal lines
// So the solution is always a prefix of vertical lines, plus the horizontal lines
// than span the full range from x = 1 to x = x_vert, where x_vert is right-most
// vertical line
// one implication is that horizontal lines start with x > 1 can be ignored
// and the y value of (x1, x2, y) can be ignored
int main() {
    int n, m; cin >> n >> m;
    vector<int> vertical(n), horizontal;
    for (int i = 0; i < n; ++i) cin >> vertical[i];
    for (int i = 0; i < m; ++i) {
        int x1, x2, y; cin >> x1 >> x2 >> y;
        if (x1 == 1) {
            horizontal.push_back(x2);
        }
    }
    sort(vertical.begin(), vertical.end());
    sort(horizontal.begin(), horizontal.end());
    int iv = 0, ih = 0;
    int keep = 0;
    // keep [iv..size) vertical lines
    for (; iv < vertical.size(); ++iv) {
        while (ih < horizontal.size() && horizontal[ih] < vertical[iv]) ih++;
        int curr = ih + vertical.size() - iv;
        keep = max(keep, curr);
    }
    // throw away all vertical lines
    int full;
    for (full = horizontal.size()-1; full >= 0; --full) {
        if (horizontal[full] < 1000000000) break;
    }
    keep = max(keep, full + 1);
    int ans = vertical.size() + horizontal.size() - keep;
    cout << ans << endl;
}
