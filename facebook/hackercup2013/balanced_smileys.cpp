// balanced_smileys.cpp

#include <cstring>
#include <iostream>
#include <string>
using namespace std;

bool dp[105][105];

bool isparen(char ch)
{
    return ch == '(' || ch == ')';
}

int main()
{
    int T; cin >> T; cin.ignore(1024, '\n');
    for (int i=0; i<T; ++i) {
        string line; getline(cin, line);
        memset(dp, 0, sizeof dp);
        int n = line.length();
        // len = 1 is true except lparen and rparen
        for (int p=0; p<n; ++p) if (!isparen(line[p]))
            dp[p][p+1] = true;
        // len = 2 is true if (), two nonparen, or : then paren
        for (int p=0; p+1<n; ++p) {
            char c1 = line[p], c2 = line[p+1];
            if (c1 == '(' && c2 == ')') dp[p][p+2] = true;
            if (!isparen(c1) && !isparen(c2)) dp[p][p+2] = true;
            if (c1 == ':') dp[p][p+2] = true;
        }
        for (int len=3; len <=n; ++len)
        for (int s=0; s+len<=n; ++s) {
            if (line[s] == '(' && line[s+len-1] == ')' && dp[s+1][s+len-1]) {
                dp[s][s+len] = true; continue;
            }
            for (int j=s+1; j<s+len; ++j)
                if (dp[s][j] && dp[j][s+len]) { dp[s][s+len] = true; break; }
        }
        string yes = "YES", no = "NO";
        cout << "Case #" << i+1 << ": ";
        if (dp[0][n]) cout << yes << endl;
        else cout << no << endl;
    }
}
