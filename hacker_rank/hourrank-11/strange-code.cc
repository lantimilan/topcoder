// strange-code.cc
// 3, 6, 12, ...
// binary search till pass t
// then it is val
// 1 => val
// 2 => val-1
// t => val-t+1
#include <iostream>
using namespace std;

int main() {
    long long t; cin >> t;
    long long val = 3;
    while (t > val) {
        t -= val;
        val *= 2;
    }
    cout << (val - t + 1) << endl;
}
