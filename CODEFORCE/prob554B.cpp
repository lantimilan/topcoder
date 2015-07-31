// prob554B.cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// one of the rows can be made clean, and this will decide which columns to
// operate on.

bool isClean(char ch) {
    return ch == '1';
}

char flip(char ch) {
    if (ch == '0') return '1';
    else return '0';
}

int main() {
    int n; cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    int best = 0;
    for (int clean = 0; clean < n; ++clean) {
        vector<string> tmp = grid;
        for (int col = 0; col < n; ++col) if (!isClean(tmp[clean][col])) {
            for (int row = 0; row < n; ++row) {
                tmp[row][col] = flip(tmp[row][col]);
            }
        }
        //for (int i = 0; i < n; ++i) cout << tmp[i] << endl;
        int total = 0;
        for (int row = 0; row < n; ++row) {
            bool rowClean = true;
            for (int col = 0; col < n; ++col) if (!isClean(tmp[row][col]))
                rowClean = false;
            total += rowClean;
        }
        best = max(best, total);
    }
    cout << best << endl;
}
