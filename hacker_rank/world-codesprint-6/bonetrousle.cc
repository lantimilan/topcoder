// bonetrousle.cc
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// Look at the sums
// b = 1
// 1, 2, 3, ..., k
// b = 2
// (1, 2) (2,3) (3, 4)
// (1, 3) (2,4)
// (1, 4) (2,5)
// (1, 5)
// b = 3
// (1, 2, 3) (2, 3, 4)
// (1, 2, 4)
// ...
// now for b
// (1, 2, ..., b) ... (1, k-b+2, ..., k-1, k)
// (2, 3, ..., b+1) ... (2, k-b+2, ..., k-1, k)
// ...
// (k-b+1, k-b+2, ..., k-1, k)
// In general, there is a solution iff n is within
// [(1,2,...,b), (k-b+1,k-b+2,...,k-1,k)]
vector<long long> chosen;

// Returns true if top cnt elements in [1..last] is larger than sum.
bool check_high(long long sum, long long last, long long cnt) {
    assert(last >= cnt);
    for (int i = 0; i < cnt; ++i) {
        sum -= (last-i);
        if (sum < 0) return true;
    }
    return (sum <= 0);
}

// Returns true if min cnt elements in [1..last], that is [1..cnt] is
// smaller or equal to sum.
bool check_low(long long sum, long long cnt) {
    for (int i = 1; i <= cnt; ++i) {
        sum -= i;
        if (sum < 0) return false;
    }
    return true;
}

int solve(long long sum, long long base, long long last, long long cnt) {
    // cout << sum << ' ' << base << ' ' << last << ' ' << cnt << endl;
    // if (!check_high(sum, last, cnt)) { return -1; }
    if ((2 * sum + cnt-1)/ cnt > last + last - cnt + 1) { return -1; }
    // if (!check_low(sum, cnt)) { return -1; };
    if (2* sum < (1 + cnt) * cnt) { return -1; }
    // long long hi = (last + last - cnt + 1) * cnt / 2;
    // long long lo = (1 + cnt) * cnt / 2;
    // if (sum < lo || sum > hi) {
    //    return -1;
    // }
    if (cnt == 1) {
        chosen.push_back(sum + base);
        return 0;
    }
    // integer overflow in last * cnt
    long long diff;
    if ((sum * 2 + cnt-2) / (cnt-1) <= (last + last - cnt + 2)) {
        diff = 1;
    } else {
        long long suffix = (last + last - cnt + 2) * (cnt -1) / 2;
        diff = sum - suffix;
    }
    chosen.push_back(base + diff);
    return solve(sum-diff*cnt, base+diff, last-diff, cnt-1);
}

vector<long long> solve2(long long sum, long long last, long long cnt) {
    vector<long long> ans;
    long long base = 0;
    for (; cnt > 1; --cnt) {
        long long diff;
        if ((sum * 2 + cnt-2) / (cnt-1) <= (last + last - cnt + 2)) {
            diff = 1;
        } else {
            long long suffix = (last + last - cnt + 2) * (cnt -1) / 2;
            diff = sum - suffix;
        }
        ans.push_back(diff + base);
        base += diff;
        sum -= diff * cnt;
        if (sum < 0) { return vector<long long>(); }
        last -= diff;
        if (last < 0) { return vector<long long>(); }
    }
    if (1 <= sum && sum <= last) {
        ans.push_back(sum + base);
        return ans;
    } else {
        return vector<long long>();
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        long long n, k, b; cin >> n >> k >> b;
        /*
        chosen.clear();
        int ret = solve(n, 0, k, b);
        if (ret < 0) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < chosen.size(); ++i) {
                if (i) { cout << ' '; }
                cout << chosen[i];
            }
            cout << endl;
        }
        */
        vector<long long> ans = solve2(n, k, b);
        if (ans.empty()) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < ans.size(); ++i) {
                if (i) { cout << ' '; }
                cout << ans[i];
            }
            cout << endl;
        }
    }
}

// Accepted, finally
// recursion => iteration
// integer overflow => use division to check larger/smaller, ceiling
