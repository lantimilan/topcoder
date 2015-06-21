// prob552A.cpp
#include <iostream>
using namespace std;

int A[105][105];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
        --x1; --y1; --x2; --y2;
        for (int r = y1; r <= y2; ++r)
        for (int c = x1; c <= x2; ++c)
            A[r][c]++;
    }
    int sum = 0;
    for (int r = 0; r < 100; ++r)
    for (int c = 0; c < 100; ++c)
        sum += A[r][c];
    cout << sum << endl;
}
