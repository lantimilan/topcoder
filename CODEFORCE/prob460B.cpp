// prob460B.cpp
//
// 0 < s(x) <= 9*9 = 81

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long mypow(int base, int expo)
{
    long long ans = 1;
    for (int p = 0; p < expo; ++p)
        ans *= base;
    return ans;
}

int main()
{
    vector<int> sol;
    int a, b, c; cin >> a >> b >> c;
    for (int s = 1; s <= 81; ++s) {
        long long x = b * mypow(s, a) + c;
        if (x >= 1e9) continue;
        // validate
        int dsum = 0;
        int y = x;
        while (y) {
            dsum += y % 10;
            y /= 10;
        }
        if (x == b * mypow(dsum, a) + c) sol.push_back(x);
    }
    sort(sol.begin(), sol.end());
    cout << sol.size() << endl;
    for (int i = 0; i < sol.size(); ++i) cout << sol[i] << endl;
}
