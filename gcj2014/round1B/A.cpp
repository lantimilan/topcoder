// A.cpp
//
// for each block of consecutive repeating char, find min cost to make them
// with same count



#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

int calc(vector<int> vec)
{
    int vmax = *max_element(vec.begin(), vec.end());
    int cost = vmax * vec.size();
    for (int c = 1; c <= vmax; ++c) {
        int cur = 0;
        for (int i = 0; i < vec.size(); ++i)
            cur += abs(c - vec[i]);
        cost = min(cost, cur);
    }
    return cost;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    int N; cin >> N;
    vector<string> vs(N);
    for (int i = 0; i < N; ++i) {
        cin >> vs[i];
    }
    int cur[105] = {0};
    int ans = 0;
    for (int i = 0; i < vs[0].size(); ) {
        char ch = vs[0][i];
        while (i < vs[0].size() && vs[0][i] == ch) ++i;
        // all strings starting cur[j] must have a nonempty block of ch
        vector<int> blocks(N);
        for (int j = 0; j < N; ++j) {
            // must find ch immediately
            if (cur[j] >= vs[j].size() || vs[j][cur[j]] != ch) {
                cout << "Fegla Won" << endl;
                return;
            }
            int start = cur[j];
            for (; cur[j] < vs[j].size() && vs[j][cur[j]] == ch; ++cur[j])
                ;
            blocks[j] = cur[j] - start;
        }
        int cost = calc(blocks);
        ans += cost;
    }
    // all strings must exhaust now
    for (int j = 0; j < N; ++j) {
        if (cur[j] < vs[j].size()) {
            cout << "Fegla Won" << endl;
            return;
        }
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
