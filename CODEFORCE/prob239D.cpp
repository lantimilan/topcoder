// seems only need to check whether min is by itself or same with others
// move others can only make things worse, min is smaller and max cannot get smaller

#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long int64;

int64 a[100000+5];
int64 b[100000+5];

int main()
{
    int n, h; cin >> n >> h;

    int minpos = -1;
    for (int i=0; i<n; ++i) {
        cin >> a[i];
        b[i] = a[i];
        if (minpos < 0 || a[i] < a[minpos])
            minpos = i;
    }

    sort(b, b+n);
    bool split = false;
    int64 diff, low, high;
    low = b[0] + b[1];
    high = b[n-1] + b[n-2];
    diff = high - low;

    // separate min
    low = b[0]+b[1] + h;
    high = b[0]+b[n-1]+h;
    if (n>=3) {
        low = min(low, b[1] + b[2]);
        high = max(high, b[n-1] + b[n-2]);
    }
    if (high >= low && high - low < diff) {
        diff = high - low;
        split = true;
    }
    cout << diff << endl;
    for (int i=0; i<n; ++i) {
        if (i) cout << ' ';
        if (i==minpos) cout << (split ? 2 : 1);
        else cout << 1;
    }
    cout << endl;
}
