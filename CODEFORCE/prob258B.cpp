//
#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

const int MOD = int(1e9+7);
int cap[10];
int dp[10][10][10];  // (len, four, seven) ways with length <= len
int cnt[10];
int groupcnt[10][10];  // (lucky, g)

int fact(int n)
{
    int ans=1;
    for (int i=1; i<=n; ++i)
        ans *= i;
    return ans;
}

int add(int a, int b)
{
    return ((int64)a + b) % MOD;
}

int mult(int a, int b)
{
    return (int64)a * b % MOD;
}

int perm(int n, int r)
{
    if (n < r) return 0;
    int ans = 1;
    for (int i=n-r+1; i<=n; ++i)
        ans = mult(ans, i);
    return ans;
}

int choose(int n, int r)
{
    if (n < r) return 0;
    int ans = 1;
    for (int i=n-r+1; i<=n; ++i)
        ans *= i;
    for (int i=1; i<=r; ++i)
        ans /= i;
    return ans;
}

int mypow(int a, int n)
{
    int ans = 1;
    for (int i=0; i<n; ++i)
        ans *= a;
    return ans;
}

int gen(int len, int four, int seven)
{
    if (four < 0 || seven < 0) return 0;
    assert(len >= 0);
    if (len < four + seven) return 0;
    int ans = 1;
    ans = mult(ans, choose(len, four)); len -= four;
    ans = mult(ans, choose(len, seven)); len -= seven;
    ans = mult(ans, mypow(8, len));
    return ans;
}

// to build array of len,
// append 0, 1, ..., d
int calc(int len, int four, int seven)
{
    if (four < 0 || seven < 0) return 0;
    if (len == 0) return four == 0 && seven == 0;
    if (dp[len][four][seven] >= 0)
        return dp[len][four][seven];
    int d = cap[len-1];
    int &ans = dp[len][four][seven];
    ans = 0;
    for (int x=0; x<=d; ++x) {
        if (x < d) {
            if (x == 4) {
                ans = add(ans, gen(len-1, four-1, seven));
            } else if (x == 7) {
                ans = add(ans, gen(len-1, four, seven-1));
            } else {
                ans = add(ans, gen(len-1, four, seven));
            }
        } else {
            if (x == 4) {
                ans = add(ans, calc(len-1, four-1, seven));
            } else if (x == 7) {
                ans = add(ans, calc(len-1, four, seven-1));
            } else {
                ans = add(ans, calc(len-1, four, seven));
            }
        }
    }
    return ans;
}

/* wrong logic
**
** the problem is to find number of ways to assign id to the six other
** groups such that sum of lucky digits strictly smaller than
** the Elephant group
** current idea is to use 6 nested loops
**
*************************************************************
int get_group(int lucky, int g, int maxlucky, int rem, int tally[])
{
    if (lucky < 0 || rem < 0) return 0;
    if (g==0) {
        int ans;
        if (lucky > 0) ans = 0;
        else {
            ans = fact(6);  // 6 groups
            for (int i=0; i<10; ++i) cout << i << ',' << tally[i] << ' '; cout << endl;
            for (int i=0; i<10; ++i)
                ans /= fact(tally[i]);
            assert(ans > 0);
        }
        return ans;
    }

    int &ans = groupcnt[lucky][g];
    int curr;
    if (ans >= 0) return ans;
    ans = 0;
    tally[maxlucky]++;
    curr = mult(rem, get_group(lucky-maxlucky, g-1, maxlucky, rem-1, tally));
    tally[maxlucky]--;
    ans = add(ans, curr);
    for (int l=0; l < maxlucky; ++l) {
        tally[l]++;
        curr = mult(cnt[l], get_group(lucky-l, g-1, l, cnt[l]-1, tally));
        tally[l]--;
        ans = add(ans, curr);
    }
    return ans;
}
*/

int main()
{
    int m; cin >> m;
    memset(dp, -1, sizeof dp);
    memset(cnt, 0, sizeof cnt);
    memset(groupcnt, -1, sizeof groupcnt);

    if (m==int(1e9)) { m--; cnt[0]++; }

    memset(cap, 0, sizeof cap);
    for (int i=0; i<10; ++i) {
        cap[i] = m % 10; m /= 10;
    }
    int len = 9;
    for (int four=0; four <= len; ++four)
    for (int seven=0; seven + four <= len ; ++seven) {
        int lucky = four + seven;
        cnt[lucky] = add(cnt[lucky], calc(len, four, seven));
    }
    cnt[0]--;  // zero does not count
    //for (int i=0; i<10; ++i) cout << cnt[i] << ' '; cout << endl;
    // cnt[] is correct
    int ans = 0;
    int id[10];
    for (id[0] = 0; id[0] < 10; ++id[0])
    for (id[1] = 0; id[1] < 10; ++id[1])
    for (id[2] = 0; id[2] < 10; ++id[2])
    for (id[3] = 0; id[3] < 10; ++id[3])
    for (id[4] = 0; id[4] < 10; ++id[4])
    for (id[5] = 0; id[5] < 10; ++id[5])
    {
        int luckycnt[10] = {0};
        int sum = 0, curr = 1;
        for (int i=0; i<6; ++i) { sum += id[i]; luckycnt[id[i]]++; }
        for (int x = 0; x < 10; ++x) {
            curr = mult(curr, perm(cnt[x], luckycnt[x]));
        }
        for (int lucky=sum+1; lucky < 10; ++lucky) {
            ans = add(ans, mult(cnt[lucky], curr));
        }
    }
    cout << ans << endl;
}

// CF OJ is having issue, still in queue
//
// to find numbers with certain property that is less than or equal to cap
// first break cap into an array of digits
// then count by length
// ways at len is by appending 0 to 9 to ways at len-1 (length <= len-1)
// for digit < d, the low order digits can be anything
// for digits = d, the low order digits cannot form a number exceeding low parts of cap
