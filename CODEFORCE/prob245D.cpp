// algorithm:
// a1 = b12 | b13 | b14 | ... | b1n
//
// proof: for a bit, if both a1 and a2 are set, then it will be set in
// the calculated a1, if only one of them is set, then setting both
// a1 and a2 to zero is consistent with b_ij
//
#include <iostream>
using namespace std;

int a[105];

int main()
{
    int n; cin >> n;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            int b;
            cin >> b;
            if (i != j) a[i] |= b;
        }
    }
    for (int i=0; i<n; ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << endl;
}
