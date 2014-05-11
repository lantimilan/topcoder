// A.cpp
// if there is a solution, it must be 0, 1, 0, 1, ...

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int points[105];
int start[105];
int end[105];
int color[105];

bool check(const vector<pair<int, int> > & sorted, int ss, int ee)
{
    int cnt[2] = {0};
    for (int i = 0; i < sorted.size(); ++i) {
        int pos = sorted[i].first;
        int cc = color[i];
        if (ss <= pos && pos <= ee) cnt[cc]++;
    }
    return (abs(cnt[0] - cnt[1]) <= 1);
}

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> points[i];
    for (int i = 0; i < m; ++i) cin >> start[i] >> end[i];

    vector<pair<int, int> > sorted(n);
    for (int i = 0; i < n; ++i) sorted[i] = make_pair(points[i], i);
    sort(sorted.begin(), sorted.end());

    for (int i = 0; i < n; ++i) {
        color[i] = i & 1;
    }

    // check all segments
    bool good = true;
    for (int i = 0; i < m; ++i) if (!check(sorted, start[i], end[i])) {
        good = false; break;
    }
    if (good) {  // print colors
        vector<int> ans(n);
        for (int i = 0; i < n; ++i) {
            int id = sorted[i].second;
            ans[id] = color[i];
        }
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}
