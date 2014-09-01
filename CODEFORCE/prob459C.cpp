// prob459C.cpp
//
// need ceil(n/k) days to get a solution
// so d >= ceil(n/k) or ans is -1

#include <iostream>
using namespace std;

int main()
{
    int n, k, d;
    cin >> n >> k >> d;

    int need = (n + k-1) / k;
    if (need <= 1) {
        for (int i = 0; i < d; ++i) {
            for (int j = 1; j <= n; ++j) {
                cout << j << ' ';
            }
            cout << endl;
        }
        return 0;
    }
    if (need > d) {
        cout << -1 << endl;
        return 0;
    }
    /*
    for (int i = 0; i < d; ++i) {
        int shift = i;
        for (int j = 0; j < n; ++j) {
            int bus = (j + shift) % k + 1;
            cout << bus << ' ';
        }
        cout << endl;
    }
    */
}
