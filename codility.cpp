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
