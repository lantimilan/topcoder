// prob574C.cpp
#include <iostream>
using namespace std;

long long a[100000+5];
int twos[100000+5];
int threes[100000+5];

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int maxtwo = 0, maxthree = 0;

    for (int i = 0; i < n; ++i) {
        int val = a[i];
        int two = 0, three = 0;
        while (val % 2 == 0) {
            val /= 2; ++two;
        }
        while (val % 3 == 0) {
            val /= 3; ++three;
        }
        twos[i] = two;
        threes[i] = three;
        maxtwo = max(maxtwo, two);
        maxthree = max(maxthree, three);
    }

    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < maxtwo - twos[i]; ++x) a[i] *= 2;
        for (int x = 0; x < maxthree - threes[i]; ++x) a[i] *= 3;
    }

    bool equal = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[0]) equal = false;
    }
    cout << (equal ? "YES" : "NO") << endl;
}
