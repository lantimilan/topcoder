// snakes.cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> PII;

PII snakes[200000+5];

const int P = 1e9+7;

map<int, vector<vector<int>>> slots;

int calc(const vector<int> &vec) {
    int n = vec.size();
    int sum = 0, sum2 = 0;
    for (int k : vec) {
        sum += k; if (sum >= P) sum -= P;
        sum2 += 1LL * k * k % P; if (sum2 >= P) sum2 -= P;
    }

    int t1 = 1LL * (n-1) * sum2 % P;
    int t2 = 1LL * sum * sum % P - sum2;
    if (t2 < 0) t2 += P;

    int ans = t1 - t2;
    if (ans < 0) ans += P;
    return ans;
}

void solve(int tcase) {
    slots.clear();
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int x, h; cin >> x >> h;
        snakes[i].first = x;
        snakes[i].second = h;
    }
    sort(snakes, snakes+N);

    stack<int> heights;
    for (int i = 0; i < N; ++i) {
        int h = snakes[i].second;
        int x = snakes[i].first;
        while (!heights.empty() && heights.top() < h) {
            heights.pop();
        }
        if (heights.empty() || heights.top() > h) {
            heights.push(h);
            slots[h].push_back(vector<int>(1, x));
        } else {
            if (slots[h].empty()) {
                slots[h].push_back(vector<int>(1, x));
            } else {
                slots[h].back().push_back(x);
            }
        }
    }

    int ans = 0;
    for (const auto &kv : slots) {
        for (const auto &vec : kv.second) {
            // calculate sum_(i<j) (X_j - X_i)^2
            // = (n-1) sum X_i^2 - ((sum X_i)^2 - sum X_i^2)
            int t = calc(vec);
            ans += t;
            if (ans >= P) ans -= P;
        }
    }

    // output
    cout << "Case #" << tcase << ": ";
    cout << ans << endl;
}

int main() {
    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        solve(t);
    }
}
