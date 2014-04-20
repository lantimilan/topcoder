// prob418B.cpp
//
// m is only 20
// so try all 2^20 combinations
//
// dp[n][1<<20] is min cost to use friend[1..n] to solve mask problems
// init: dp[0][0] = 0
// state transition:
//
// from dp[n-1][] to dp[n]
// case 1: skip friend[n]
// dp[n-1][mask] -> dp[[n][mask]
// case 2: use friend[n]
// dp[n-1][mask] -> dp[n][mask | friend_problems] + cost for friend[n]
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

// dp[i][mask] is the minimum cost when using i-th friend's monitor
// and solving problems in mask
long long dp[2][1<<20];  // save space since got Memory Limit Exceeded

struct Person {
    int monitor;
    int mask;
    int cost;
    bool operator<(const Person &p2) const {
        if (monitor != p2.monitor) return monitor < p2.monitor;
        if (mask != p2.mask) return mask < p2.mask;
        if (cost != p2.cost) return cost < p2.cost;
        return false;
    }
};

void update(long long &a, long long b)
{
    if (a < 0 || a > b) a = b;
}

int main()
{
    // read input
    int n, m, b; cin >> n >> m >> b;  // n friends, m problems, b for monitor
    Person people[105];
    for (int i = 0; i < n; ++i) {
        int rubles, monitor, nsolve;
        cin >> rubles >> monitor >> nsolve;
        int mask = 0;
        for (int j = 0; j < nsolve; ++j) {
            int id; cin >> id; assert(1 <= id && id <= m);
            --id;
            mask |= 1<<id;
        }
        people[i].monitor = monitor;
        people[i].mask = mask;
        people[i].cost = rubles;
    }
    sort(people, people + n);

    long long best = -1;
    memset(dp, -1, sizeof dp);
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        int i1 = i & 1;
        int i2 = (i+1) & 1;
        for (int mask = 0; mask < (1 << m); ++mask)
        if (dp[i1][mask] >= 0) {
            int diff;
            if (i > 0) diff = people[i].monitor - people[i-1].monitor;
            else diff = people[i].monitor;

            // skip friend[i]
            update(dp[i2][mask], dp[i1][mask] + (long long)b * diff);
            // use friend[i]
            int newmask = mask | people[i].mask;
            long long cost = people[i].cost;
            update(dp[i2][newmask], dp[i1][mask] + cost + (long long)b * diff);
        }
        long long cur = dp[i2 & 1][(1<<m)-1];
        if (cur >= 0) update(best, cur);
        memset(dp[i1], -1, sizeof dp[i1]);
    }

    cout << best << endl;
}


// 1. operator< needs to be const member
// 2. use dp[2][] to save space
// 3. use i1, i2 to make code easier to write/read
// 4. reset dp[i1][] to -1 for next iteration
