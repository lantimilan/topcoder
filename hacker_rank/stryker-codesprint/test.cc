// test.cc
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    // some numbers, like 65.1, is really 65.099999999999
    // so when mult by 1000, it will be 65099
    // when div by 1000.0, it becomes 65.099
    // even 65100 div by 1000.0 gives 65.09999999
    // round up may be and option too.
    // use d=65.1, will get 65.099 back
    double d; cin >> d; cout << fixed << setprecision(20) << d << endl;
    int n = d * 1000 + 1e-6;
    double d2 = n / 1000.0 + 1e-6;
    cout << n << ' ' << d2 << endl;
}
