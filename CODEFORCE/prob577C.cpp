// prob577C.cpp
#include <iostream>
#include <vector>
using namespace std;

int isprime[1005];
int primes[1005];
int P;

void init() {
    for (int i = 0; i <= 1000; ++i) isprime[i] = true;
    isprime[0] = isprime[1] = false;
    for (int i = 2; i <= 1000; ++i) if (isprime[i]) {
        for (int j = i+i; j <= 1000; j+=i) {
            isprime[j] = false;
        }
    }

    P = 0;
    for (int i = 2; i <= 1000; ++i) if (isprime[i]) {
        primes[P++] = i;
    }

    for (int i = 0; i < 20; ++i) {
        cerr << primes[i] << ' ';
    }
    cerr << endl;
}

int main() {
    init();
    int n; cin >> n;
    vector<int> ans;
    for (int x = 0; x < P; ++x) {
        int pr = primes[x];
        int d = pr;
        while (d <= n) {
            ans.push_back(d);
            d *= pr;
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << endl;
}
