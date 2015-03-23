// prob527A.cpp

// euclid's algorithm

#include <iostream>
using namespace std;

int main()
{
    long long a, b; cin >> a >> b;
    long long ans = 0;
    while (b > 0) {
        ans += a / b;
        a %= b;
        long long t = b; b = a; a = t;
    }
    cout << ans << endl;
}
