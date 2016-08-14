// a-couple-and-their-passions.cc

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

set<string> guests;
string cities[255];
double lat[255];
double lon[255];
vector<string> passions[255];

const double PI = 3.14159265359;

double deg2rad(double d) {
    return d / 180 * PI;
}

double calc(int a, int b) {
    double radius = 6371;
    double l1 = deg2rad(lat[a]);
    double l2 = deg2rad(lat[b]);
    double g1 = deg2rad(lon[a]);
    double g2 = deg2rad(lon[b]);
    return acos( sin(l1) * sin(l2) +
        cos(l1) * cos(l2) * cos(g2 - g1))
        * radius;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        for (int j = 0; j < m; ++j) {
            string passion; cin >> passion;
            guests.insert(passion);
        }
    }
    // cerr << guests.size() << endl;
    int y; cin >> y;
    for (int i = 0; i < y; ++i) {
        cin >> cities[i];
        cin >> lat[i] >> lon[i];
        int z; cin >> z;
        for (int j = 0; j < z; ++j) {
            string p; cin >> p;
            passions[i].push_back(p);
        }
    }

    int ids[2] = {-1, -1};
    int nmax = 0;
    double dist2 = 0.0;
    for (int i = 0; i < y; ++i)
    for (int j = i+1; j < y; ++j) {
        set<string> covered;
        for (const auto& p : passions[i]) {
            if (guests.count(p)) {
                covered.insert(p);
            }
        }
        for (const auto& p : passions[j]) {
            if (guests.count(p)) {
                covered.insert(p);
            }
        }
        int score = covered.size();
        if (score > nmax) {
            ids[0] = i; ids[1] = j;
            nmax = score; dist2 = calc(i, j);
        } else if (score == nmax) {
            double d2 = calc(i, j);
            if (d2 < dist2) {
                ids[0] = i; ids[1] = j;
                nmax = score; dist2 = calc(i, j);
            }
        }
    }
    // cerr << "ids " << ids[0] << " " << ids[1] << endl;
    vector<string> vec(2);
    for (int i = 0; i < 2; ++i) {
        vec[i] = cities[ids[i]];
    }
    sort(vec.begin(), vec.end());
    cout << vec[0] << " " << vec[1] << endl;
}
