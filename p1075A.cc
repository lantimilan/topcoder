// p1075A.cc
#include <iostream>
using namespace std;

int main() {
    long long n; cin >> n;
    long long x, y; cin >> x >> y;

    long long d = max(x-1, y-1);
    long long t = max(n-x, n-y);
    cout << (d <= t ? "White" : "Black") << endl;
}
