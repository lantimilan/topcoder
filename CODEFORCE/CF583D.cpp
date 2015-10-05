// CF583D.cpp
#include <iostream>
#include <vector>
using namespace std;

// at most N rows with >=2 distinct values
// because if not, then we can charge one value to each row and then have
// D distinct values for D such rows, yet we have at most N distinct values.
// and = solve(n^2) + (T-n^2) * max cnt of any element
int n, T;
int a[105];
int cnt[305];

int calc(const vector<int>& vec) {
    int dp[10005] = {0};
    int longest = 0;

    for (int p = 0; p < vec.size(); ++p) {
        dp[p] = 1;
        for (int q = p-1; q >= 0; --q) if (vec[q] <= vec[p]) {
            dp[p] = max(dp[p], dp[q]+1);
        }
        longest = max(longest, dp[p]);
    }
    return longest;
}

int main() {
    cin >> n >> T;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<int> vec;
    for (int i = 0; i < min(T, n); ++i)
    for (int k = 0; k < n; ++k)
        vec.push_back(a[k]);

    int maxcnt = 0;
    for (int v = 1; v <= 300; ++v) maxcnt = max(cnt[v], maxcnt);

    int ans = maxcnt * max(0, (T - n));
    ans += calc(vec);
    cout << ans << endl;
}
