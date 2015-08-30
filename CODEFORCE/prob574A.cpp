// prob574A.cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int n; cin >> n;
    int a[103]; for (int i = 0; i < n; ++i) cin >> a[i];
    int ans = 0;
    while (true) {
        int *kmax = max_element(a+1, a+n);
        if (*kmax >= a[0]) {
            (*kmax)--; a[0]++; ans++;
        } else {
            break;
        }
    }
    cout << ans << endl;
}
