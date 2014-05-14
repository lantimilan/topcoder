// B.cpp
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
using namespace std;

const int MOD = 1e9+7;
const int INF = 100;

int total_blocks[105];  // number of blocks (same char subarray) in vec[i]
int used[105];
int head[30];  // ch appear as head
int tail[30];  // ch appear as tail
int mid[30];  // ch appear in the middle
int single[30];  // single ch string
int fact[105];

int process(const string &s, int cnt[])
{
    memset(cnt, 0, sizeof cnt);
    int i, j;  // block [i, j)
    for (i = 0; i < s.size(); i = j) {
        for (j = i+1; j < s.size() && s[j] == s[i]; ++j)
            ;

        char ch = s[i];
        cnt[ch-'a']++;
    }
    for (int xc = 0; xc < 26; ++xc) {
        if (cnt[xc] > 1) return INF;
    }
    int ans = 0;
    for (int xc = 0; xc < 26; ++xc) {
        ans += cnt[xc];
    }
    return ans;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    memset(head, 0, sizeof head);
    memset(tail, 0, sizeof tail);
    memset(mid, 0, sizeof mid);
    memset(single, 0, sizeof single);
    memset(total_blocks, 0, sizeof total_blocks);
    memset(used, 0, sizeof used);

    int N; cin >> N;
    vector<string> vec(N);
    for (int i = 0; i < N; ++i) {
        cin >> vec[i];
    }

    for (int i = 0; i < N; ++i) {
        string s = vec[i];
        int cnt[30] = {0};
        int nblock = process(s, cnt);
        if (nblock >= INF) {
            // no valid train
            cout << 0 << endl;
            return;
        }
        total_blocks[i] = nblock;
        if (nblock == 1) single[s[0] - 'a']++;
        else {
            int x;
            x = s[0] - 'a';
            head[x]++; cnt[x] = 0;
            x = s[s.size()-1] - 'a';
            tail[x]++; cnt[x] = 0;
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                x = ch - 'a';
                if (cnt[x]) mid[x]++;
            }
        }
    }
    /*
    for (int x = 0; x < 26; ++x) {
        cout << char(x + 'a') << ' ' << head[x] << ' ' << tail[x] << ' '
            << mid[x] << ' ' << single[x] << endl;
    }
    */
    // every ch must have
    // if mid == 1, then head = tail = 0
    // else head <= 1, tail <= 1
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        int x = ch - 'a';
        if (mid[x] > 1) { cout << 0 << endl; return; }
        else if (mid[x] == 1) {
            if (head[x] > 0 || tail[x] > 0) {
                cout << 0 << endl; return;
            }
        } else {  // mid[x] == 0
            if (head[x] > 1 || tail[x] > 1) {
                cout << 0 << endl; return;
            }
        }
    }

    vector<int> mult;  // each mult[i] is an independent train, ans = prod(mult[])
    // now construct trains
    // first for two chars
    while (true) {
        int char_map[30] = {0};  // ch appear in this train
        // train must start with head[ch] == 1 and tail[ch] == 0
        int start;
        for (start = 0; start < N; ++start) {
            if (!used[start] && total_blocks[start] >= 2) {
                char ch = vec[start][0];
                if (tail[ch-'a'] == 0) break;
            }
        }
        if (start >= N) break;
        while (true) {  // construct a train from start
            used[start] = 1;
            const string &s = vec[start];
            for (int x = 0; x < s.size(); ++x) {
                char_map[s[x]-'a'] = 1;
            }
            head[s[0]-'a'] = 0;
            tail[s[s.size()-1]-'a'] = 0;
            char lead = s[s.size()-1];
            int next;
            for (next = 0; next < N; ++next) {
                if (!used[next] && total_blocks[next] >= 2)
                    if (vec[next][0] == lead)
                        break;
            }
            if (next >= N) break;
            else start = next;
        }
        int cur = 1;
        for (int xc = 0; xc < 26; ++xc) {
            if (char_map[xc]) {
                cur = (long long)cur * fact[single[xc]] % MOD;
                single[xc] = 0;
            }
        }
        mult.push_back(cur);
    }
    /*
    cout << "mult: ";
    for (int i = 0; i < mult.size(); ++i) {
        cout << mult[i] << ' ';
    } cout << endl;
    */
    // now all head[ch] and tail[ch] must be 0
    for (int xc = 0; xc < 26; ++xc) {
        if (head[xc] || tail[xc]) {
            cout << 0 << endl;
            return;
        }
    }
    // then for one chars
    for (int xc = 0; xc < 26; ++xc) if (single[xc]) {
        mult.push_back(fact[single[xc]]);
    }
    int ans = 1;
    for (int x = 0; x < mult.size(); ++x) {
        ans = (long long)ans * mult[x] % MOD;
    }
    ans = (long long)ans * fact[mult.size()] % MOD;
    cout << ans << endl;
}

int main()
{
    // init fact[]
    fact[0] = 1;
    for (int i = 1; i <= 100; ++i) fact[i] = (long long)fact[i-1] * i % MOD;

    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
