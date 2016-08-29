// reviews.cc
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

string topic_list[105];
set<string> topics;
map<string, int> reviewers[2000];

bool within(long long t) {
    return 1465948800L <= t && t < 1468540800L;
}

string sanitize(string s) {
    string s2;
    for (int i = 0; i < s.length(); ++i) {
        char ch = s[i];
        s2 += tolower(ch);
        //if (isalpha(ch)) {
        //    s2 += tolower(ch);
        //}
    }
    return s2;
}

void print() {
    for (int i = 0; i <= 1000; ++i)
    if (!reviewers[i].empty()) {
        cout << i << ": ";
        for (const auto &p : reviewers[i]) {
            cout << p.first << "," << p.second
                << " ";
        }
        cout << endl;
    }
}

int count_char(const string &s) {
    return s.length();
    /*
    int ans = 0;
    for (char ch : s) {
        ans += (ch != ' ');
        // ans += isalpha(ch);
    }
    return ans;
    */
}

int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        string t; cin >> t;
        t = sanitize(t);
        topics.insert(t);
        topic_list[i] = t;
    }
    for (int i = 0; i < m; ++i) {
        int r; cin >> r;
        long long t; cin >> t;
        cin.ignore(1024, '\n');
        string b; getline(cin, b); // cout << b << endl;

        int score = 0;
        score += (within(t) ? 20 : 10);
        score += (count_char(b) >= 100 ? 20 : 10);

        b = sanitize(b);
        set<string> seen;
        for (const string &s : topics) {
            if (b.find(s) != string::npos) {
                // cout << s << endl;
                seen.insert(s);
            }
        }
        /*
        istringstream iss(b);
        string tp;
        while (iss >> tp) {
            tp = sanitize(tp);  // cout << "tp: " << tp << endl;
            //if (topics.count(tp)) {
            //    seen.insert(tp);
            //}
            for (const string & s : topics) {
                if (tp.find(s) != string::npos) {
                    seen.insert(s);
                }
            }
        }
        */
        for (const string &s : seen) {
            reviewers[r][s] += score;
        }
    }

    // print();

    map<string, int> score_list;
    map<string, int> reviewer_list;
    for (int r = 0; r <= 1000; ++r) {
        for (const auto &p : reviewers[r]) {
            string tp = p.first;
            int score = p.second;
            if (score > score_list[tp]) {
                score_list[tp] = score;
                reviewer_list[tp] = r;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        string tp = topic_list[i];
        int ans = -1;
        if (reviewer_list.count(tp)) {
            ans = reviewer_list[tp];
        }
        cout << ans << endl;
    }
}

// WA
// + time range is correct. confirmed in forum.
// + body 100 or more characters, does space count, does punctuation count
// + seems we need to lowercase all char
//
// + got substring the other way round, use a simple testcase to find the bug.
// and print internal state to show score.
// 1 1
// spa
// 1 103384
// I love spa'guetti
//
// Test 0 and 2 passed (so test 2 checks substring)
// still failing, Test 1, 3, and 4 (discussed that test 4 checks time range)
// Test 1 uses that body.length >= 100, this length includes all char, space and
// punctuation
//
// Now pass Test 0, 1, and 2
//
// Can passion include space or punctuation? seems YES on punctuation
// Got AC

