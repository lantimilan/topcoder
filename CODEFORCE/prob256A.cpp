#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;

map<int,int> mp;
int a[4005];
int b[4005];
int dp[4005][4005];
int nxt[4005][4005]; // pos, val

int main()
{
    int n, k; cin >> n;
    for (int i=0; i<n; ++i) { cin >> a[i]; b[i] = a[i]; }
    sort(b, b+n);
    k=0;
    for (int i=0; i<n; ++i) if (!mp.count(b[i])) mp[b[i]] = k++;
    for (int i=0; i<n; ++i) a[i] = mp[a[i]];

    memset(nxt, -1, sizeof nxt);
    for (int i=0; i<n; ++i)
    for (int j=i+1; j<n; ++j)
        if (nxt[i][a[j]] < 0) nxt[i][a[j]] = j;

    for (int i=0; i<n; ++i)
    for (int k=0; k<n; ++k)
        dp[i][k] = 1;

    for (int i=0; i<n; ++i)
    for (int k=0; k<n; ++k) {
        int j = nxt[i][k];
        if (j>=0)
            dp[j][a[i]] = max(dp[j][a[i]], dp[i][k] + 1);
    }

    int best = 0;
    for (int i=0; i<n; ++i)
    for (int k=0; k<n; ++k)
        best = max(best, dp[i][k]);
    cout << best << endl;
}
// Accepted