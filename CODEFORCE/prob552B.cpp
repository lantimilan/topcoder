// prob552B.cpp
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    long long ndigits = 0;
    int d = 1;
    long long f = 1;
    while (n >= f * 10 -1) {
        long long cnt = f * 9; // max of f is 9e8, mult 9 is 9e9, larger than 2e9
        ndigits += d * cnt;
        ++d; f *= 10;
    }
    ndigits += d * (n - f + 1);

    /*
    int ref = 0;
    for (int i = 1; i <= n; ++i) {
        int d = 0;
        int val = i;
        while (val) {
            val /= 10; ++d;
        }
        ref += d;
    }
    //assert(ndigits == ref);
    */
    cout << ndigits << endl;
}
