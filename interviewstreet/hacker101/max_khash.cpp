// max_khash.cpp
//
// binary search

#include <cassert>
#include <iostream>
using namespace std;

int m, n;

char table[505][505];
int row[505][505];
int col[505][505];

int main()
{
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) table[i][j] = s[j];
    }

//    for (int i = 0; i < m; ++i)
//    {
//    for (int j = 0; j < n; ++j)
//        cout << table[i][j];
//    cout << endl;
//    }

    // row span from (i,j) to right
    for (int i = 0; i < m; ++i) {
        row[i][n-1] = (table[i][n-1] == '.');
        for (int j = n-2; j >= 0; --j)
            if (table[i][j] == 'x') row[i][j] = 0;
            else row[i][j] = row[i][j+1] + 1;
    }

    for (int j = 0; j < n; ++j) {
        col[n-1][j] = (table[n-1][j] == '.');
        for (int i = n-2; i >= 0; --i)
            if (table[i][j] == 'x') col[i][j] = 0;
            else col[i][j] = col[i+1][j] + 1;
    }

    int best = 0;
    for (int i = 0; i < m; ++i)
    for (int j = 0; j < n; ++j)
    for (int w = 2; w <= n; ++w)
    for (int h = 2; h <= m; ++h)
    if (i+h-1 < m && j+w-1 < n)
    {
        if (row[i][j] >= w && row[i+h-1][j] >= w
            && col[i][j] >= h && col[i][j+w-1] >= h)
            {
            best = max(best, 2*((w-1) + (h-1)));
            }
    }

    if (best == 0) cout << "impossible\n";
    else cout << best << endl;
}
