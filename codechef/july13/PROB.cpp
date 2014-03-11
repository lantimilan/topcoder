// PROB.cpp
//
// 1. without T4, the answer is T1 / (T1 + T2) and T3 is irrelevant
// Proof by induction on T3.
//
// 2. Since T4 is chosen uniformly among T1+T2+T3, and T4 <= T1 + T2,
// we claim T4 is irrelevant too.
// That is, the answer is simply T1 / (T1 + T2)
// Proof: TODO
//
// Implementation is trivial

#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
    int T; cin >> T;
    while (T--) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << fixed << setprecision(10) << 1.0 * a / (a + b) << endl;
    }
}

// Accepted
