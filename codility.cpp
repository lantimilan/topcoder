// Given a table A of N integers from 0 to N-1 calculate the smallest such index P, that that {A[0],...,A[N-1]} = {A[0],...,A[P]}.
int solution ( int A[], int N ) {
    int used[1000000+5] = {0};
    int taken[1000000+5] = {0};

    int i, cnt=0;
    for (i = 0; i < N; ++i) {
        if (used[A[i]] == 0) cnt++;
        used[A[i]] = 1;
    }
    for (i = 0; i < N; ++i) {
        if (taken[A[i]] == 0) {
            cnt--; taken[A[i]] = 1;
        }
        if (cnt == 0) break;
    }
    return i;
}


// 1. number_of_disc_intersections
// Compute intersections between sequence of discs.
// you can also use includes for example:
#include <algorithm>
int binsearch(const vector<long long> &vec, long long val)
{
    int N = vec.size();
    int lo = -1, hi = N;  // vec[lo] < val, vec[hi] >= val
    while (lo + 1 < hi) {
        int m = (lo + hi) / 2;
        if (vec[m] >= val) hi = m;
        else lo = m;
    }
    return hi;
}

int solution ( const vector<int> &A ) {
    typedef pair<long long,long long> pii;
    int N = A.size();
    if (N <= 1) return 0;
    vector<pii> intervals(N);
    for (int i = 0; i < N; ++i) intervals[i] = pii(i + (long long)A[i], i - (long long)A[i]);
    sort(intervals.begin(), intervals.end());
    vector<long long> used;
    used.push_back(intervals[0].first);
    int cnt = 0;
    for (int i = 1; i < N; ++i) {
        long long left = intervals[i].second;
        long long right = intervals[i].first;
        int pos = binsearch(used, left);
        cnt += used.size() - pos;
        if (cnt > 10000000) return -1;
        used.push_back(right);
    }
    return cnt;
}


// count number of palindrome substrings with length >= 2
// you can also use includes for example:
// #include <algorithm>
#include <vector>
#include <cassert>

int solution ( const string &s) {
    if (s.empty()) return 0;
    int n = s.size();
    int c[2] = {0, 1};
    vector<int> len(2*n);

    for (int i = 0; i < 2*n; ++i) len[i] = 0;
    len[0] = 0; len[1] = 1;

    for (int i = 2; i < 2*n; ++i) {
        int k = c[i&1];
        int l1, l, r, p, q;
        int j = 2*k - i;

        l = (k-len[k])/2;
        r = (k+len[k])/2 - 1;
        if (i/2 > r) {  // s[pos] out of range of center
            len[i] = i & 1;
            l = i/2; r = (i-1)/2;
            l1 = -1;
        } else {  // s[pos] within range of center
            len[i] = min(len[j], 2*r - i + 2);
            assert(j >= 0);
            l1 = (j-len[j])/2;
        }
        if (l1 > l) continue;  // left image within boundary, len[i] fixed
        p = r-len[i]; q = r+1;
        while (0 <= p && q < n && s[p] == s[q]) {
            p--; q++;
        }
        len[i] = q-p-1;
        if (q-1 > r) c[i&1] = i;  // move center to next pos
    }
    int ans = 0;
    for (int i = 0; i < 2*n; ++i) {
        ans += len[i]/2;
        if (ans > 1e8) return -1;
    }
    return ans;
}

//  1. min_abs_sum
// Given array of integers, find the lowest absolute sum of elements.
#include <algorithm>
#include <cstring>
// you never need to remember difference more than 100, the max element
int dp[20000+5][205];
int OFFSET = 100;
int solution ( const vector<int> &A ) {
    memset(dp, 0, sizeof dp);
    int N = A.size();
    dp[0][OFFSET] = 1;
    for (int i = 1; i <= N; ++i)
        for (int sum = 0; sum <= 200; sum++) {
            int prev, val;
            val = abs(A[i-1]);
            prev = sum - val;
            if (0 <= prev && prev <= 200 && dp[i-1][prev])
                dp[i][sum] = 1;
            prev = sum + val;
            if (0 <= prev && prev <= 200 && dp[i-1][prev])
                dp[i][sum] = 1;
        }
    int best = 200;
    for (int sum = 0; sum <= 200; sum++) if (dp[N][sum]) {
        int val = abs(sum - OFFSET);
        best = min(best, val);
    }
    return best;
}

