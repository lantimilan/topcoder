// A.cpp

// swap to a[n-1], then a[n-2] ...
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long eval(int a[], int size, int l, int r, int budget)
{
    vector<int> inner, outer;
    for (int i = 0; i < size; ++i) {
        if (l <= i && i <= r) inner.push_back(a[i]);
        else outer.push_back(a[i]);
    }
    while (budget--) {
        // replace inner min with outer max if better
        int inpos = 0, outpos = -1;
        for (int pos = 1; pos < inner.size(); ++pos) {
            if (inner[pos] < inner[inpos])
                inpos = pos;
        }
        for (int pos = 0; pos < outer.size(); ++pos) {
            if (outpos < 0 || outer[pos] > outer[outpos])
                outpos = pos;
        }
        if (outpos < 0) break;
        if (inner[inpos] >= outer[outpos]) break;
        swap(inner[inpos], outer[outpos]);
    }
    long long ans = 0;
    for (int i = 0; i < inner.size(); ++i)
        ans += inner[i];
    return ans;
}

int main()
{
    int n, k; cin >> n >> k;
    int a[205];
    for (int i = 0; i < n; ++i) cin >> a[i];

    // eval all l,r pairs
    long long ans = -2000LL;
    for (int l = 0; l < n; ++l)
    for (int r = l; r < n; ++r)
        ans = max(ans, eval(a, n, l, r, k));
    cout << ans << endl;
}
