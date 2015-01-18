// A.cpp
#include <algorithm>
#include <iostream>
using namespace std;

int get_val(int digits[], int nd)
{
    int val = 0;
    for (int i = 0, c = 1; i < nd; ++i, c *= 10) {
        val += digits[i] * c;
    }
    return val;
}

void solve(int tcase)
{
    int N; cin >> N;
    int digits[10] = {0};
    int nd = 0;
    int start = N;
    do {
        digits[nd++] = start % 10;
        start /= 10;
    } while (start);

    int vmax = N, vmin = N;
    for (int i = 0; i < nd; ++i)
    for (int j = i+1; j < nd; swap(digits[i], digits[j]), ++j) {
        swap(digits[i], digits[j]);
        if (digits[nd-1] == 0) continue;
        int val = get_val(digits, nd);
        if (val > vmax) vmax = val;
        if (val < vmin) vmin = val;
    }

    cout << "Case #" << tcase << ": "
        << vmin << " " << vmax << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
