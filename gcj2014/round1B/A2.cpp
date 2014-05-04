// template.cpp
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

string parse_unique(string s)
{
    char ch = '*';
    string ans;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == ch) {}
        else { ch = s[i]; ans += s[i]; }
    }
    return ans;
}

int get_min(vector<int> blocks)
{
    int maxval = *max_element(blocks.begin(), blocks.end());
    int best = maxval * blocks.size();
    for (int c = 1; c <= maxval; ++c) {
        int cur = 0;
        for (int i = 0; i < blocks.size(); ++i)
            cur += abs(blocks[i] - c);
        best = min(best, cur);
    }
    return best;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    // read input
    int N; cin >> N;
    vector<string> vecstr(N);
    for (int i = 0; i < N; ++i) {
        cin >> vecstr[i];
    }
    // squeeze into string with unique char
    vector<string> vec_unique(N);
    for (int i = 0; i < N; ++i) {
        vec_unique[i] = parse_unique(vecstr[i]);
    }
    // all vec_unique[] must be identical
    bool good = true;
    for (int i = 0; i < N-1; ++i) {
        if (vec_unique[i] != vec_unique[i+1]) {
            good = false; break;
        }
    }
    if (!good) {
        cout << "Fegla Won" << endl;
        return;
    }

    // compress all into str_unique
    int ans = 0;
    string target = vec_unique[0];
    vector<int> position(N, 0);  // starting position for each string
    for (int i = 0; i < target.size(); ++i) {
        char ch = target[i];
        // min cost to get block into target[i]
        vector<int> blocks(N);
        for (int j = 0; j < N; ++j) {
            assert(vecstr[j][position[j]] == ch);
            int start = position[j];
            while (position[j] < vecstr[j].size() && vecstr[j][position[j]] == ch) {
                position[j]++;
            }
            blocks[j] = position[j] - start;
        }
        ans += get_min(blocks);
    }
    cout << ans << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
