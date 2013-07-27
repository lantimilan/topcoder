// prob329A.cpp
//
// necessary condition: every row has one free cell, or every column has a cell
// it is also sufficient
// moreover, one placement is to put one cell in each row

#include <vector>
#include <iostream>
using namespace std;

int main()
{
    int n; cin >> n;
    bool good = true;
    vector<int> cells(n);
    char mat[105][105];
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) mat[i][j] = s[j];
    }

    for (int i = 0; i < n; ++i) {
        int j;
        for (j = 0; j < n; ++j) if (mat[i][j] == '.') {
            cells[i] = j;
            break;
        }
        if (j >= n) { good = false; break; }
    }
    if (good) {
        for (int i = 0; i < n; ++i) {
            cout << i+1 << ' ' << cells[i]+1 << endl;
        }
        return 0;
    }
    good = true;
    for (int j = 0; j < n; ++j) {
        int i;
        for (i = 0; i < n; ++i) if (mat[i][j] == '.') {
            cells[j] = i;
            break;
        }
        if (i >= n) { good = false; break; }
    }
    if (good) {
        for (int j = 0; j < n; ++j) {
            cout << cells[j]+1 << ' ' << j+1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
}
