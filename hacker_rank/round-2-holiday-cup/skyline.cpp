// skyline.cpp
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    int a[20];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (n % 2 == 0) {
        cout << "Not perfect" << endl;
        return 0;
    }
    for (int i = 0; i < n/2; ++i) {
        if (a[i] >= a[i+1]) {
            cout << "Not perfect" << endl;
            return 0;
        }
    }
    for (int i = 0; i < n/2; ++i) {
        if (a[i] != a[n-1-i]) {
            cout << "Not perfect" << endl;
            return 0;
        }
    }
    cout << "Perfect" << endl;
}
