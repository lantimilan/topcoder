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
    int absval = abs(val);
    char buf[1000];
    sprintf(buf, "%d.%03d", absval/1000, absval%1000);
// an alternative is to print int and then insert decimal point
//    string str;
//    ostringstream oss(str);
//    oss << absval / 1000 << "." << absval % 1000;
//    string s2 = oss.str();
//    return ((val < 0) ? "-" : "") + padding(s2);
    // return padding(oss.str());
    return ((val<0) ? "-" : "") + string(buf);
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
    const string notfound = "Point doesn't exist in the bucket.";
    int n, b; cin >> n >> b;
    for (int i = 0; i < n; ++i) {
        int id; cin >> id;
        string x, y, z; cin >> x >> y >> z;
        // cout << x << ' ' << y << ' ' << z << endl;
        x = padding(x);
        y = padding(y);
        z = padding(z);
        // cout << x << ' ' << y << ' ' << z << endl;
        int x2, y2, z2;
        x2 = str2int(x);
        y2 = str2int(y);
        z2 = str2int(z);
        // cout << x2 << ' ' << y2 << ' ' << z2 << endl;
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
        if (!points.count(id)) {
            cout << notfound << endl;
            continue;
        }
        int zindex = points[id][2]; // cout << "id " << id << " " << zindex << endl;
        if (toupper(op[0]) == 'F') {
            if (bucket.count(zindex)) {
                vector<int> v = points[id];
                char buf[1000];
                sprintf(buf, "%d = (%s,%s,%s)", id,
                    int2str(v[0]).c_str(),
                    int2str(v[1]).c_str(),
                    int2str(v[2]).c_str());
                cout << buf << endl;
            } else {
                cout << notfound << endl;
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
                cout << notfound << endl;
            }
        }
    }
}
