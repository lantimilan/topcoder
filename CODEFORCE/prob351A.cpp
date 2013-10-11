// prob351A.cpp

// given 2n numbers, n = 2000,
// find the best partition such that after pairs rounded, sum is closest to
// original sum

// let upp and low be round up and round down numbers, then the difference
// is sum[low] + (n - sum[upp]), so we are to minimize sum[low] - sum[upp]
// since sum[low] + sum[upp] = sum, we are to find the closest sum[low] to
// sum/2
//
// sum can be as large as 2n * 10000 = 2 * 2000 * 10000 = 4*10^7
// so sum/2 = 2*10^7
// 2000 * 2 * 10^7 is too slow
//
// wait, you only care about the last 3 digits, so only 0 to 999, that is
// 1000 possible different values
// so you can match 1 to 999, 2 to 998, etc
// until you only have lower ones like 0 to 499
// or higher ones like 500 to 999
// notice that you can have at most one 500
//
// now what?
// you have 2*2000 = 4000 numbers
// each being either 1 to 500, or 500 to 999
//
// SOLUTION:
// actually the solution is simple, once you see it
// pairing things up, and round one down, one up, the difference is
// a1 + a2 - 1000, except pairs with both first and second being zero
// since we are looking at the last three digits
// we want to minimize the difference, let there be 2n numbers so we
// have n pairs, then we have n pairs, and we want to
// minimize the sum of the difference,
// it seems we should first group zero values, then the rest can be
// grouped arbitrarily?
//
// proof that zeroes must be together if more than two zeroes available
// if there are two pairs each with one member being zero, then group
// the two zeros and make the other two a new pair can only reduce the
// difference
//
// STILL WRONG
// here is a correct solution
//
// let (a1, a2) be the fractional pair we start and the integral target
// be (k1, k2)
// if a1 and a2 are both > 0, then k1 and k2 must be 0 and 1000
// if a1 and a2 are both = 0, then k1 = k2 = 0
// if a1 = 0 and a2 > 0, then we can make 0, 1000 or 0,0
//
// in other words, target is always 1000 unless we have a1 = 0
// we have n pairs, we can get as many as #zero of 0s
// we can get as little as (#zero - other) /2,
// notice that #zero and other must be same parity, because the sum
// of the two is 2n, an even number
//
// we can try all possible number of 0s for target, the rest is 1000
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int getFrac(const string &s)
{
    int res = 0;
    for (int i = 3; i > 0; --i) {
        int d = s[s.size()-i] - '0';
        res = res * 10 + d;
    }
    return res;
}

int main()
{
    int sum = 0;
    int cnt[1005] = {0};
    int n; cin >> n;
    for (int i = 0; i < 2*n; ++i) {
        string s; cin >> s;
        int k = getFrac(s);
        sum += k;
        cnt[k]++;
    }
    int best = 4*n*1000;
    int zeromin = (cnt[0] - (2*n - cnt[0])) / 2;
    if (zeromin < 0) zeromin = 0;
    int zeromax = cnt[0];
    if (zeromax > n) zeromax = n;

    for (int zero = zeromin; zero <= zeromax; ++zero) {
        int other = n - zero;
        int target = 1000 * other;
        int diff = abs(sum - target);
        best = min(diff, best);
    }

    char buf[30];
    sprintf(buf, "%d.%03d", best/1000, best%1000);
    cout << buf << endl;
}

