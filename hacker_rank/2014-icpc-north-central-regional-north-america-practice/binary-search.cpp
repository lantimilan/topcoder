// binary-search.cpp
#include <iostream>
#include <map>
using namespace std;

map<int, long long> cache;

long long calc(int n) {
    if (n == 0) return 0;
    if (cache.count(n)) return cache[n];
    long long ans = n + calc(n / 2) + calc((n-1) / 2);
    return cache[n] = ans;
}

int main() {
    int t = 0;
    int n;
    while (cin >> n) {
        cout << "Case " << (++t) << ": ";
        cout << calc(n) << endl;
    }
}
