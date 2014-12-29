// prob499C.cpp
//
// observation: the number of hops are the number of lines that separates
// the two points

#include <iostream>
using namespace std;

int sgn(long long l)
{
    if (l == 0) return 0;
    else if (l > 0) return 1;
    else return -1;
}

int main()
{
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    int n; cin >> n;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        long long a, b, c; cin >> a >> b >> c;
        long long v1, v2;
        v1 = a * x1 + b * y1 + c;
        v2 = a * x2 + b * y2 + c;
        if (sgn(v1) * sgn(v2) < 0) ans++;
    }
    cout << ans << endl;
}

