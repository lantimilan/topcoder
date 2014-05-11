// D.cpp
//
// the problem is actually simple
// g1[][], best score start at [0][0]
// g2[][], best score start at [n-1][m-1]
// g3[][], best score start at [n-1][0]
// g4[][], best score start at [0][m-1]
//
// they must meet at some (i,j)
// g1[i][j] + g2[i][j] + g3[i][j] + g4[i][j]
// - 4*a[i][j]

#include <cstring>
#include <iostream>
using namespace std;

int g1[1005][1005], g2[1005][1005], g3[1005][1005], g4[1005][1005];
int a[1005][1005];

void chmax(int &x, int y)
{
    if (x < y) x = y;
}

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        cin >> a[i][j];

    // g1[0][0], i+1 or j+1
    memset(g1, 0, sizeof g1);
    g1[0][0] = a[0][0];
    for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
        if (i+1 < n) chmax(g1[i+1][j], g1[i][j] + a[i+1][j]);
        if (j+1 < m) chmax(g1[i][j+1], g1[i][j] + a[i][j+1]);
    }

    // g2[n-1][m-1], i-1 or j-1
    memset(g2, 0, sizeof g2);
    g2[n-1][m-1] = a[n-1][m-1];
    for (int i = n-1; i >= 0; --i)
    for (int j = m-1; j >= 0; --j) {
        if (i-1 >= 0) chmax(g2[i-1][j], g2[i][j] + a[i-1][j]);
        if (j-1 >= 0) chmax(g2[i][j-1], g2[i][j] + a[i][j-1]);
    }

    // g3[n-1][0], i-1 or j+1
    memset(g3, 0, sizeof g3);
    g3[n-1][0] = a[n-1][0];
    for (int i = n-1; i >= 0; --i)
    for (int j = 0; j < m; ++j) {
        if (i-1 >= 0) chmax(g3[i-1][j], g3[i][j] + a[i-1][j]);
        if (j+1 < m) chmax(g3[i][j+1], g3[i][j] + a[i][j+1]);
    }

    // g4[0][m-1], i+1 or j-1
    memset(g4, 0, sizeof g4);
    g4[0][m-1] = a[0][m-1];
    for (int i = 0; i < n; ++i)
    for (int j = m-1; j >= 0; --j) {
        if (i+1 < n) chmax(g4[i+1][j], g4[i][j] + a[i+1][j]);
        if (j-1 >= 0) chmax(g4[i][j-1], g4[i][j] + a[i][j-1]);
    }

    int ans = 0;
    for (int i = 1; i < n-1; ++i)
    for (int j = 1; j < m-1; ++j) {
        // meet at a[i][j]
        // but they cannot meet in another cell as well
        // only two choice of entering, and they have matching
        // pairs of exiting
        int cur;
        cur = g1[i][j-1] + g2[i][j+1] + g3[i+1][j] + g4[i-1][j];
        chmax(ans, cur);
        cur = g1[i-1][j] + g2[i+1][j] + g3[i][j-1] + g4[i][j+1];
        chmax(ans, cur);
    }

    cout << ans << endl;
}

// each must go throught exactly n + m cells
// and they have to meet in exactly one cell

// the problem says "after they meet,  both of them will move to the next workout."
// so the meet point cannot be their end position.
// also, "when they meet, neither of them work out"
// but A start at (1,1) and B start at (n,1)
// so they cannot meet in their start position as well
