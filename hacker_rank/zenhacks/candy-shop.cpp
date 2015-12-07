#include <cstring>
#include <iostream>
using namespace std;

int units[] = {1,2,5,10,20,50,100};
long long dp[255][10];

long long calc(int N, int k) {
    if (N == 0) return 1;
    if (k == 0) return 0;

    if (dp[N][k] >= 0) return dp[N][k];
    long long &ans = dp[N][k];
    ans = calc(N, k-1);
    int val = units[k-1];
    if (N >= val) {
        ans += calc(N-val, k);
    }
    //cout << N << ' ' << k << ' ' << ans << endl;
    return ans;
}

int main() {
    memset(dp, -1, sizeof dp);
    int N; cin >> N;
    long long ans = calc(N, 7);
    cout << ans << endl;
}
