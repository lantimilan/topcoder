// TYPING.cc
// impl
#include <iostream>
#include <set>
#include <string>
using namespace std;


// 0 is left, 1 is right
int get_side(char ch) {
    if (ch == 'd' || ch == 'f') return 0;
    return 1;
}

void solve() {
    set<string> seen;
    int N; cin >> N;
    int total = 0;
    while (N--) {
        string word; cin >> word;
        int cost = 2;
        int side = get_side(word[0]);
        for (int i = 1; i < word.length(); ++i) {
            char ch = word[i];
            int next = get_side(ch);
            if (next == side) { cost += 4; }
            else { cost += 2; }
            side = next;
        }
        if (seen.count(word)) { cost /= 2; }
        seen.insert(word);
        total += cost;
    }
    cout << total << endl;
}


int main() {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}
