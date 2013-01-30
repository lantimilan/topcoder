// find_the_min.cpp
//
// watch for rand gen all zero

#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <set>
using namespace std;

set<int> avail;
multiset<int> seen;
deque<int> que;
int vec[200000+5];

void solve(int tcase)
{
    int n, k; cin >> n >> k;
    int a, b, c, r; cin >> a >> b >> c >> r;
    int val;
    multiset<int>::iterator it;
    avail.clear();
    que.clear();
    seen.clear();

    //cout << n << ' ' << k << endl;
    //cout << a << ' ' << b << ' ' << c << ' ' << r << endl;
    // m[0] = a
    // m[i] = (b*m[i-1]+c) % r
    vec[0] = a; seen.insert(a);
    for (int i=1; i<k; ++i) {
        int val = ((long long)b * vec[i-1] + c) % r;
        vec[i] = val;
        seen.insert(val);
    }
    for (int v=0; v<=k; ++v) {
        if (!seen.count(v)) avail.insert(v);
    }

    val = *avail.begin();
    vec[k] = val; avail.erase(val);
    for (int i=k+1; i<2*k+1; ++i) {
        int first = vec[i-k-1];
        it = seen.find(first);
        if (it != seen.end()) seen.erase(it);
        if (!seen.count(first)) avail.insert(first);
        assert(!avail.empty());
        int val = *avail.begin();
        vec[i] = val; avail.erase(val);
    }
    //cout << "ans " << vec[n-1] << endl;
    // and all following are continuation of this permutation
    //for (int i=0; i<k; ++i) cout << vec[i] << ' '; cout << endl;
    //for (int i=k; i<2*k+1; ++i) cout << vec[i] << ' '; cout << endl;
    //sort(vec+k, vec+2*k+1);
    //for (int i=k; i<2*k; ++i) cout << vec[i] << ' '; cout << endl;
    //for (int i=k; i<2*k+1; ++i) assert(vec[i] == i-k);
    cout << "Case #" << tcase << ": ";
    n -= k;
    n %= (k+1);
    cout << vec[k+n-1] << endl;
}

int main()
{
    int T; cin >> T;
    for (int t=1; t<=T; ++t)
        solve(t);
}

// the case
// 10^9 10^5
// 1 1 0 2
//
// which generates all 1, takes too long that I lost faith in my code
// it runs in 1m16s
//
// I was not that patient so killed the process
// would fail this problem
