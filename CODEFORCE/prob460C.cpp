// prob460C.cpp
//
// binary search

#include <iostream>
#include <queue>
using namespace std;

int a[100000+5];
int n, m, w;

bool check(int target);

int main()
{
    cin >> n >> m >> w;
    for (int i = 0; i < n; ++i) cin >> a[i];

    int lo = 1, hi = 2e9;
    while (lo + 1 < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << lo << endl;
}

bool check(int target) {
    deque<int> incr;
    long long sum = 0;
    long long need = 0;
    for (int i = 0; i < n; ++i) {
        if (incr.size() >= w) {
            int front = incr.front();
            incr.pop_front();
            sum -= front;
        }
        long long newval = a[i] + sum;
        int d;
        if (newval < target) {
            d = target - newval;
        } else {
            d = 0;
        }
        incr.push_back(d);
        sum += d;
        need += d;
    }
    return need <= m;
}
