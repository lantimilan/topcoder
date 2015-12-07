// integral-points.cpp
#include <iostream>
using namespace std;

// Pick's theorem
// A = i + b/2 -1
// area of a simple polygon with all vertices being lattice points

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    int T; cin >> T;
    while (T--) {
        long long x[3], y[3];
        for (int i = 0; i < 3; ++i) cin >> x[i] >> y[i];
        long long area2 = 0;
        for (int i = 0; i < 3; ++i) {
            int j = (i+1) % 3;
            area2 += x[i] * y[j] - x[j] * y[i];
        }
        area2 = abs(area2);

        long long b = 0;
        for (int i = 0; i < 3; ++i) {
            int j = (i+1) % 3;
            long long t1 = abs(x[j] - x[i]);
            long long t2 = abs(y[j] - y[i]);
            b += gcd(t1, t2);
        }

        long long interior = (area2 - b + 2) / 2;
        cout << interior << endl;
    }
}
