#include <iostream>
using namespace std;

int main()
{
    int n, x; cin >> n >> x;
    int ans = 0;
    int pos = 0;
    for (int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        while (pos + x < l) pos += x;
        ans += r - pos;
        pos = r;
    }
    cout << ans << endl;
}
