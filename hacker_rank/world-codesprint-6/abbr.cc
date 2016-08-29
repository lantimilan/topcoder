// abbr.cc
#include <cctype>
#include <iostream>
#include <vector>
using namespace std;

vector<int> pos[26];
int dp[1005][1005];
int dp2[1005][1005];
string a, b;

void chmax(int &a, int b) {
    if (a < b) a = b;
}

// we must use every char in b[]
// for a[i], if upper, we must use it, else we may upper it or delete it
int lcs() {
    int n1 = a.length();
    int n2 = b.length();
    for (int i = 0; i < n1; ++i)
    for (int j = 0; j < n2; ++j) {
        if (isupper(a[i])) {
            if (a[i] == b[j]) {
                dp[i][j] = 1;
                if (i > 0 && j > 0) {
                    dp[i][j] += dp[i-1][j-1];
                }
            } else {
                dp[i][j] = 0;
            }
        } else {
            dp[i][j] = (toupper(a[i]) == b[j]);
            if (i > 0 && j > 0) {
                dp[i][j] += dp[i-1][j-1];
            }
            if (i > 0) {  // delete a[i]
                chmax(dp[i][j], dp[i-1][j]);
            }
        }
    }
    return dp[n1-1][n2-1];
}

void solve() {
    cin >> a >> b;
    string yes = "YES";
    string no = "NO";
    cout << (lcs() == b.length() ? yes : no) << endl;
}

int main() {
    int q; cin >> q;
    while (q--) {
        solve();
    }
}

// Accepted
