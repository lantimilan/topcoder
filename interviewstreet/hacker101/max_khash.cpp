// max_khash.cpp
//
// binary search

#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

int m, n;

char table[505][505];
int row[505][505];
int col[505][505];
int strip[505][505];
int hop[505][505];

int main()
{
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) table[i][j] = s[j];
    }

    // row span from (i,j) to right
    for (int i = 0; i < m; ++i) {
        row[i][n-1] = (table[i][n-1] == '.');
        for (int j = n-2; j >= 0; --j)
            if (table[i][j] == 'x') row[i][j] = 0;
            else row[i][j] = row[i][j+1] + 1;
    }

    for (int j = 0; j < n; ++j) {
        col[m-1][j] = (table[m-1][j] == '.');
        for (int i = m-2; i >= 0; --i)
            if (table[i][j] == 'x') col[i][j] = 0;
            else col[i][j] = col[i+1][j] + 1;
    }

    int best = 0;
    for (int h = 2; h <= m; ++h)
    {
        memset(strip, 0, sizeof strip);
        memset(hop, 0, sizeof hop);
        // hop[i][j][h] is dist to right most consecutive hop
        for (int j = n-1; j >= 0; --j) {
            for (int i = m-1; i >= 0; --i) {
                if (i+h-1 < m) {
                    if (table[i][j] == '.' && table[i+h-1][j] == '.') {
                        hop[i][j] = 1;
                        if (j+1 < n) hop[i][j] = hop[i][j+1] + 1;
                    }
                }
            }
        }
        // find right most strip within hop
        for (int j = n-1; j >= 0; --j) {
            for (int i = m-1; i >= 0; --i) if (hop[i][j] > 0) {
                if (j+1 < n && strip[i][j+1] > 0) {
                    strip[i][j] = strip[i][j+1] + 1;
                } else {
                    if (col[i][j] >= h) strip[i][j] = 1;
                }
            }
        }

        int wmax = 0;
        for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
        if (col[i][j] >= h)
        {
            wmax = max(wmax, strip[i][j]);
        }
        //cout << h << ' ' << wmax << endl;
        if (wmax > 1)
        best = max(best, 2*(h-1 + wmax-1));
    }

    if (best == 0) cout << "impossible\n";
    else cout << best << endl;
}

// Accepted
