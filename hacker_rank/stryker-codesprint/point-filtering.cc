// point-filtering.cc
#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

map<int, vector<int>> points;
map<int, int> ztoid;  // z => id
map<int, int> bucket;  // z => id

string padding(const string &s) {
    string ans = s;
    int p;
    for (p = 0; p < s.length() && s[p] != '.'; ++p) ;
    if (p >= s.length()) {
        ans = s + ".000";
    } else {
        ans += string((p+4 - s.length()), '0');
    }
    return ans;
}

string int2str(int val) {
    string str;
    ostringstream oss(str);
    oss << val / 1000 << "." << abs(val) % 1000;
    string s2 = oss.str();
    return padding(s2);
    // return padding(oss.str());
    // return oss.str();
}

int str2int(const string &s) {
    string s2;
    for (const char ch : s) {
        if (ch != '.') s2 += ch;
    }
    istringstream iss(s2);
    int val; iss >> val;
    return val;
}

int main() {
    int n, b; cin >> n >> b;
    for (int i = 0; i < n; ++i) {
        int id; cin >> id;
        double x, y, z; cin >> x >> y >> z;
        int x2, y2, z2;
        x2 = (int)((x + 1e-6) * 1000 + 0.5);
        y2 = (int)((y + 1e-6) * 1000 + 0.5);
        z2 = (int)((z + 1e-6) * 1000 + 0.5);
        cout << x2 << ' ' << y2 << ' ' << z2 << endl;
        points[id] = {x2, y2, z2};
        bucket[z2] = id;
        if (bucket.size() > b) {
            int minz = bucket.begin()->first;
            ztoid[minz] = bucket[minz];
            bucket.erase(minz);
        }
    }
    /*
    for (const auto &p: bucket) {
        cout << p.first << " => " << p.second << endl;
    }
    for (const auto &p: ztoid) {
        cout << p.first << " => " << p.second << endl;
    }
    */
    cin.ignore(1024, '\n');
    string line;
    while (getline(cin, line)) {
        istringstream iss(line);
        string op; int id;
        iss >> op >> id;
        int zindex = points[id][2]; // cout << "id " << id << " " << zindex << endl;
        if (toupper(op[0]) == 'F') {
            if (bucket.count(zindex)) {
                vector<int> v = points[id];
                char buf[1000];
                sprintf(buf, "%d = (%.3lf,%.3lf,%.3lf)", id,
                    (v[0]+.5)/1000.0,
                    (v[1]+.5)/1000.0,
                    (v[2]+.5)/1000.0);
                cout << buf << endl;
            } else {
                cout << "Point doesn't exist in the bucket." << endl;
            }
        } else {  // remove op
            // cout << "zindex " << zindex << endl;
            if (bucket.count(zindex)) {
                if (ztoid.empty()) {
                    cout << "No more points can be deleted." << endl;
                } else {
                    cout << "Point id " << id << " removed." << endl;
                    auto kv = ztoid.rbegin();
                    // cout << "add point: " << kv->first << " " << kv->second << endl;
                    bucket[kv->first] = kv->second;
                    ztoid.erase(kv->first);
                    bucket.erase(zindex);
                }
            } else {
                cout << "Point doesn't exist in the bucket." << endl;
            }
        }
    }
}
