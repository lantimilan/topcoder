#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

bool is_prime[200];
bool semi_prime[200];
vector<int> semis;

void init() {
    for (int k = 0; k < 200; ++k) is_prime[k] = true;
    is_prime[0] = is_prime[1] = false;
    for (int k = 2; k < 200; ++k) if (is_prime[k]) {
        for (int j = k+k; j < 200; j += k) {
            is_prime[j] = false;
        }
    }
    cerr << "primes:";
    for (int i = 0; i < 200; ++i) {
        if (is_prime[i]) cerr << i << ' ';
    } cerr << endl;
    for (int i = 0; i < 200; ++i) if (is_prime[i])
        for (int j = i+1; j < 200; ++j) if (is_prime[j]) {
            if (i * j < 200) semi_prime[i * j] = true;
        }
    cerr << "semis:";
    for (int i = 0; i < 200; ++i) if (semi_prime[i]) {
        semis.push_back(i);
        cerr << i << ' ';
    } cerr << endl;
}

int main() {
    init();
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        bool good = false;
        for (const int& k : semis) {
            if (k >= N) break;
            if (semi_prime[N-k]) {
                good = true; break;
            }
        }
        cout << (good ? "YES" : "NO") << endl;
    }
}
