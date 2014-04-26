// C.cpp
//
// if one free cell, done
// else at least one cell is 0, then place that 0 at corner
// use 3 neighbors around, then arrange the rest continuously with mines

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int R0, C0;

void print(const vector<string> &vec)
{
    if (R0 < C0) {  // transpose
        vector<string> vec2(R0, string(C0,'X'));
        for (int i = 0; i < vec.size(); ++i)
        for (int j = 0; j < vec[i].size(); ++j)
            vec2[j][i] = vec[i][j];
        for (int i = 0; i < vec2.size(); ++i)
            cout << vec2[i] << endl;
    } else {
        for (int i = 0; i < vec.size(); ++i)
            cout << vec[i] << endl;
    }
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": " << endl;
    int R, C, M; cin >> R >> C >> M;
    R0 = R; C0 = C;
    if (R < C) swap(R, C);
    assert(R >= C);
    vector<string> ans(R, string(C, 'X'));

    if (C == 1) {
        for (int i = 0; i < M; ++i) ans[i][0] = '*';
        for (int i = M; i < R; ++i) ans[i][0] = '.';
        ans[R-1][C-1] = 'c';
        print(ans);
        return;
    }

    // C >= 2
    if (M + 1 == R * C) {  // only one free cell
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            ans[i][j] = '*';
        ans[R-1][C-1] = 'c';
        print(ans);
        return;
    } else {  // need at least one 0
        if (M + 4 > R * C) {
            cout << "Impossible" << endl;
            return;
        }
        ans[R-1][C-1] = 'c';
        ans[R-2][C-2] = ans[R-2][C-1] = ans[R-1][C-2] = '.';
        int mine = M;
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j) if (ans[i][j] == 'X') {
            if (mine > 0) {
                ans[i][j] = '*';
                mine--;
            }
        }
        assert(mine == 0);
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (ans[i][j] == 'X')
                ans[i][j] = '.';
        print(ans);
        return;
    }
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
