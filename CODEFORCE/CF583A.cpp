// CF583A.cpp
#include <iostream>
using namespace std;

int row[55];
int col[55];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n*n; ++i) {
        int r, c; cin >> r >> c;
        if (!row[r] && !col[c]) {
            row[r] = col[c] = 1;
            cout << (i+1) << ' ';
        }
    }
    cout << endl;
}
