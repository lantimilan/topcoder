// aquarium-tank.cpp
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef pair<double,double> pdd;

double calc_area(const vector<pdd> &polygon) {
    int n = polygon.size();
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        int j = (i+1) % n;
        double x1 = polygon[i].first;
        double y1 = polygon[i].second;
        double x2 = polygon[j].first;
        double y2 = polygon[j].second;
        area += x1*y2 - x2*y1;
    }
    return .5 * fabs(area);
}

vector<pdd> cut_chain(const vector<pdd> &chain, double height) {
    vector<pdd> subchain;
    for (int i = 0; i < chain.size(); ++i) {
        double y = chain[i].second;
        if (y < height + 1.0e-7) {
            subchain.push_back(chain[i]);
        } else {
            assert(i > 0);
            double x1, y1, x2, y2, xh;
            x1 = chain[i-1].first;
            y1 = chain[i-1].second;
            x2 = chain[i].first;
            y2 = chain[i].second;
            assert(y2 > y1);
            xh = (height - y1) * (x2 - x1) / (y2 - y1) + x1;
            subchain.push_back(make_pair(xh, height));
            break;
        }
    }
    return subchain;
}

vector<pdd> get_polygon(const vector<pdd> &myleft, const vector<pdd> &myright) {
    vector<pdd> polygon = myright;
    for (int i = myleft.size()-1; i >= 0; --i) {
        polygon.push_back(myleft[i]);
    }
    return polygon;
}

void solve(int tcase, int N) {
    double B, L; cin >> B >> L; //cout << B << ' ' << L << endl;
    // read input for polygon
    vector<pdd> polygon;
    for (int i = 0; i < N; ++i) {
        double x, y; cin >> x >> y;
        polygon.push_back(make_pair(x, y));
    }
    double ymin, ymax;
    int idmin, idmax;
    ymin = ymax = polygon[0].second;
    idmin = idmax = 0;
    for (int i = 1; i < N; ++i) {
        double y = polygon[i].second;
        if (y < ymin) {
            ymin = min(y, ymin);
            idmin = i;
        }
        if (y > ymax) {
            ymax = max(y, ymax);
            idmax = i;
        }
    }
    int next;
    next = (idmin + 1) % N;
    if (polygon[next].second == ymin) {
        idmin = next;
    }
    next = (idmax + 1) % N;
    if (polygon[next].second == ymax) {
        idmax = next;
    }

    vector<pdd> myleft, myright;
    for (int i = idmax; ; i = (i+1) % N) {
        myleft.push_back(polygon[i]);
        double y = polygon[i].second;
        if (y == ymin) break;
    }
    reverse(myleft.begin(), myleft.end());
    for (int i = idmin; ; i = (i+1) % N) {
        myright.push_back(polygon[i]);
        double y = polygon[i].second;
        if (y == ymax) break;
    }

    /*
    for (pdd p : myleft) {
        cout << fixed << setprecision(0);
        cout << p.first << "," << p.second << ' ';
    } cout << endl;
    for (pdd p : myright) {
        cout << fixed << setprecision(0);
        cout << p.first << "," << p.second << ' ';
    } cout << endl;
    */

    double target = L * 1000.0 / B; //cout << "target " << target << endl;
    double lo = ymin, hi = ymax;
    double mid;
    for (int k = 0; k < 300; ++k) {
        mid = (lo + hi) / 2;
        vector<pdd> l1 = cut_chain(myleft, mid);
        vector<pdd> r1 = cut_chain(myright, mid);
        vector<pdd> pp = get_polygon(l1, r1);
        double area = calc_area(pp);
        if (area < target) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    cout << "Case " << tcase << ": ";
    cout << fixed << setprecision(4) << mid << endl;
}

int main() {
    int tcase = 0;
    int N;
    while (cin >> N) {
        solve(++tcase, N);
    }
}
