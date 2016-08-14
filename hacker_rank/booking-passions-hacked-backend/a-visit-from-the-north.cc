// a-visit-from-the-north.cc
#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct TimeUnit {
    int day;
    int hour;
    TimeUnit() { day = hour = 0; }
    TimeUnit(int d, int h) { day = d; hour = h; }
    bool operator<(const TimeUnit &t2) const {
        if (day != t2.day) return day < t2.day;
        else return hour < t2.hour;
    }

    bool is_valid() const {
        return day > 0 && hour > 0 && *this < TimeUnit(7, 8+1);
    }

    // time (day, hour)
    // day is 1 to 7, Mon to Sun
    // hour is 8 to 23
    void advance(int incr) {
        while (hour + incr >= 24) {
            incr -= 24 - hour;
            hour = 8; day++;
        }
        hour += incr;
    }
};

typedef pair<int, int> PII;  // (next, cost)
vector<PII> graph[25];
string node_names[25];
map<string, int> node_table;
int stay[25];
TimeUnit tsp[1<<20][22];
pair<int,int> pred[1<<20][22];


void split(const string &s, string &city, int &length) {
    int p;
    city = "";
    for (p = 0; p < s.length(); ++p) {
        if (s[p] == ',') break;
        city += s[p];
    }
    length = 0;
    for (++p; p < s.length(); ++p) {
        length = length * 10 + s[p] - '0';
    }
}

void split2(const string &s, string &from, string &to, int &length) {
    int p;
    for (p = 0; p < s.length() && s[p] != ','; ++p) {
        from += s[p];
    }
    for (++p; p < s.length() && s[p] != ','; ++p) {
        to += s[p];
    }
    length = 0;
    for (++p; p < s.length(); ++p) {
        length = length * 10 + s[p] - '0';
    }
}

int count_bits(int b) {
    int s = 0;
    while (b) {
        ++s;
        b &= b-1;
    }
    return s;
}

int main() {
    int n; cin >> n; cin.ignore(1024, '\n');
    for (int i = 0; i < n; ++i) {
        string line; getline(cin, line);
        string city; int length;
        split(line, city, length);
        node_table[city] = i;
        node_names[i] = city;
        stay[i] = length;
    }
    node_table["Bevagna"] = n;

//    for (int i = 0; i < n; ++i) {
//        cout << i << ": " << node_names[i] << " " << stay[i] << endl;
//    }

    int e; cin >> e; cin.ignore(1024, '\n');
    for (int i = 0; i < e; ++i) {
        string line; getline(cin, line);
        string from; string to; int length;
        split2(line, from, to, length);
        int u = node_table[from];
        int v = node_table[to];
        if (length <= 24 - 8) {  // cannot travel for more than 16h
                                 // otherwise have to sleep mid-travel
            graph[u].push_back(make_pair(v, length));
            graph[v].push_back(make_pair(u, length));
        }
    }

//    for (int i = 0; i < n; ++i) {
//        cout << i << ": ";
//        for (auto p : graph[i]) {
//            cout << p.first << "," << p.second << " ";
//        }
//        cout << endl;
//    }

    // compute tsp
    for (int i = 0; i < (1<<n); ++i)  // subset mask
    for (int j = 0; j <= n; ++j) {  // last stop at city
        tsp[i][j] = TimeUnit(-1, -1);
        pred[i][j] = make_pair(-1, -1);
    }
    tsp[0][n] = TimeUnit(1, 8);
    for (int mask = 0; mask < (1<<n); ++mask)
    for (int last = 0; last <= n; ++last) if (tsp[mask][last].is_valid()) {
        // cout << mask << " " << last << " " << tsp[mask][last].day << ","
        //    << tsp[mask][last].hour << endl;
        for (auto p : graph[last]) {
            int next = p.first;
            int travel = p.second;
            TimeUnit tnew = tsp[mask][last];
            if (tnew.hour + travel > 24) {
                // should fix Test 16
                // cout << mask << ' ' << last << ' ' << next << endl;
                continue;  // cannot travel beyond midnight
            }
            tnew.advance(travel);
            tnew.advance(stay[next]);
            if ((1<< next & mask) == 0) {  // city not visited before
                int newmask = mask | 1<<next;
                if (!tsp[newmask][next].is_valid() || tnew < tsp[newmask][next]) {
                    tsp[newmask][next] = tnew;
                    pred[newmask][next] = make_pair(mask, last);
                }
            }
        }
    }

    /*
    for (int i = 0; i < n; ++i) {
        TimeUnit t = tsp[(1<<n)-1][i];
        cout << node_names[i] << ": " << t.day << "," << t.hour << endl;
    }
    */

    int best_mask = -1;
    int best_last = -1;
    int best_bits = 0;
    for (int b = 0; b < (1<<n); ++b)
    for (int i = 0; i < n; ++i) if (tsp[b][i].is_valid()) {
        int bits = count_bits(b);
        if (bits > best_bits) {
            best_mask = b;
            best_last = i;
            best_bits = bits;
        }
    }
    // cout << best_mask << " " << best_last << " " << best_bits << endl;

    if (best_mask < 0) {
        cout << "NONE" << endl;
        return 0;
    }

    vector<int> ans;
    int mm = best_mask;
    int dd = best_last;
    while (mm > 0) {
        // cout << mm << " " << dd << endl;
        ans.push_back(dd);
        pair<int, int> p = pred[mm][dd];
        mm = p.first; dd = p.second;
    }
    reverse(ans.begin(), ans.end());
    assert(!ans.empty());
    for (int node : ans) {
        cout << node_names[node] << endl;
    }
}

// should have no RE or Seg fault (array can be at most 2^20 * 21)

// will get RE because array out of bounds
// Test 9, 10, 11, 17 Seg fault
// Test 16 WA (still WA, after fixing time cannot go beyond Sunday 8AM)
