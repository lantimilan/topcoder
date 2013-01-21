// first digit 1 to K-1
// other digits can have 0 to ceil(N-1)/2 zeros
//

#include <iostream>
using namespace std;

long long choose(int n, int r)
{
    long long ans = 1;
    for (int i=0; i<r; ++i)
        ans *= (n-i);
    for (int i=1; i<=r; ++i)
        ans /= i;
    return ans;
}

int main()
{
    int N, K; cin >> N >> K;
    long long ans = 0;
    for (int zero = 0; zero <= N/2; ++zero) {
        long long tmp = 1;
        int other = N-1 - zero;
        if (other < zero-1) continue;
        for (int i=0; i<other; ++i) tmp *= (K-1);
        other -= (zero-1);
        // (other+zero choose zero)
        tmp *= choose(other+zero, zero);
        ans += tmp;
    }
    ans *= (K-1);
    cout << ans << endl;
}

// 4731447  12:08:10 21 Jan 2013
// lantimilan  1009. K-based Numbers   C++ Accepted    0.015   196 KB
