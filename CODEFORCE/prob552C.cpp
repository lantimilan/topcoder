// prob552C.cpp
#include <iostream>
using namespace std;

int main() {
    int w, m; cin >> w >> m;
    int sub[105] = {0};
    int len = 0;
    for (len = 0; m > 0; ++len) {
        sub[len] = m % w; m /= w;
    }
    int carry = 0;
    for (int i = 0; i < len; ++i) {
        int curr = carry + sub[i];
        if (curr % w == 0 || curr % w == 1) {  // can use 0
            carry = curr / w;
        } else {  // use 1
            curr += 1;
            if (curr % w == 0) {
                carry = curr / w;
            } else {
                cout << "NO" << endl;
                return 0;
            }
        }
    }
    cout << "YES" << endl;
}
