// CF583B.cpp
#include <iostream>
using namespace std;

int a[1005];
int done[1005];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int cracked = 0;
    int pass = 0;
    int rem = n;
    int last = 0;
    while (rem) {
        pass++;
        if (pass & 1) {
        for (int i = last; i < n; ++i) if (!done[i]) {
            if (cracked >= a[i]) {
                last = i;
                done[i] = 1;
                cracked++;
                rem--;
            }
        }
        } else {
        for (int i = last; i >= 0; --i) if (!done[i]) {
            if (cracked >= a[i]) {
                last = i;
                done[i] = 1;
                cracked++;
                rem--;
            }
        }
        }
        //cout << pass << ' ' << last << ' ' << cracked << endl;
    }
    cout << pass-1 << endl;
}
