// LEMUSIC.cpp
//
// let there be B distinct bands
// then the first B items in the optimal ordering but have distinct bands
// Why? if not we can move all the duplicated bands to the end, this
// does not affect un-moved items, but the moved items can only be sweeter


#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef long long int64;
typedef pair<int,int> pii;

vector<pii> all;
vector<pii> pre, post;

bool cmp(const pii &p1, const pii &p2)
{
    if (p1.second != p2.second) return p1.second < p2.second;
    if (p1.first != p2.first) return p1.first < p2.first;
    return false;
}

void solve()
{
    int N; cin >> N;
    for (int i = 0; i < N; ++i) {
        int B, L; cin >> B >> L;
        all.push_back(pii(B,L));
    }
    sort(all.begin(), all.end());
    for (int i = 0; i < N; ++i) {
        if (pre.empty() || all[i].first != pre.back().first)
            pre.push_back(all[i]);
        else
            post.push_back(all[i]);
    }
    sort(pre.begin(), pre.end(), cmp);
    int64 ans = 0;
    for (int i = 0; i < pre.size(); ++i) {
        int64 cur = (int64)pre[i].second * (i+1);
        ans += cur;
    }
    for (int i = 0; i < post.size(); ++i) {
        int B = pre.size();
        int64 cur = (int64)post[i].second * B;
        ans += cur;
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    while (T--) {
        all.clear(); pre.clear(); post.clear();
        solve();
    }
}
