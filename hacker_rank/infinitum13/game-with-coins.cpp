// game-with-coins.cpp
#include <iostream>
using namespace std;

// f(a,b) = 1 if force a win
// f(a,0) = f(0,b) = 1;
// f(a,b) = 1 - min(f(a-1,b), f(a,b-1)) for a > 0 and b > 0
// f(1,1) = 0, f(2,1) = 1 - min(f(2,0), f(1,1) = 1
// claim: f(a,b) = 1 if (a ^ b) & 1 = 1
// proof by induction.

int main() {
    int T; cin >> T;
    while (T--) {
        int a, b; cin >> a >> b;
        string first = "First", second = "Second";
        if (a == 0 || b == 0) {
            cout << first << endl;
        } else {
            cout << (((a ^ b) &1) ? first : second) << endl;
        }
    }
}
