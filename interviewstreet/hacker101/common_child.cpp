// common_child.cpp

// longest common subsequence

#include <iostream>
#include <string>
using namespace std;

string s1, s2;
int dp[5005][5005];

int lcs(const string &a, const string &b)
{
    int na = a.length(), nb = b.length();
    dp[0][0] = 0;
    for (int i = 0; i <= na; ++i)
    for (int j = 0; j <= nb; ++j)
    {
        if (i > 0 && j > 0) {
            if (a[i-1] == b[j-1]) dp[i][j] = max(dp[i][j], dp[i-1][j-1] + 1);
            else dp[i][j] = max(dp[i][j], dp[i-1][j-1]);
        }
        if (i > 0) {
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
        }
        if (j > 0) {
            dp[i][j] = max(dp[i][j], dp[i][j-1]);
        }
    }
    return dp[na][nb];
}

int main()
{
    cin >> s1 >> s2;
    cout << lcs(s1,s2) << endl;
}
