// emmas-notebook.cpp
#include <iostream>
using namespace std;

int main() {
    int t; cin >> t;
    long long ans;
    if (t+1 & 1) {
        ans = 1LL * t/2 * (t/2+1) + t/2 + 1;
    } else {
        int m = (t+1)/2;
        ans = 1LL * m * (m+1);
    }
    cout << ans -1 << endl;
}
