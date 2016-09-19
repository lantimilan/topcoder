// point2.cc
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

int main() {
    const string notfound = "Point doesn't exist in the bucket.";
    int n, b; cin >> n >> b;
    for (int i = 0; i < n; ++i) {
        int id; cin >> id;
        double x, y, z; cin >> x >> y >> z;
        // cout << x << ' ' << y << ' ' << z << endl;
        int x2, y2, z2;
        x2 = (int)(x * 1000);
        y2 = (int)(y * 1000);
        z2 = (int)(z * 1000);
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
                // sprintf(buf, "%d = (%.3lf,%.3lf,%.3lf)", id,
                sprintf(buf, "%d = (%.3d,%.3d,%.3d)", id,
                // mult by 0.001 or div by 1000.0 will change the value.
                    // v[0] * 0.001, v[1] * 0.001, v[2] * 0.001);
                    // v[0]/1000.0, v[1]/1000.0, v[2]/1000.0);
                    v[0], v[1], v[2]);
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
