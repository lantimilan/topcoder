// world-cup-team-formation.cpp
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int a[10];
    for (int i = 0; i < 10; ++i) cin >> a[i];
    sort(a, a+10); reverse(a, a+10);
    int ans = a[0] + a[2] + a[4];
    cout << ans << endl;
}
