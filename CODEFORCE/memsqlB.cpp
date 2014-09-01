// memsqlB.cpp

#include <cmath>
#include <utility>
#include <iostream>
using namespace std;

double square(double x)
{
    return x * x;
}

double dist(pair<int,int> p1, pair<int,int> p2)
{
    double x1 = p1.first, y1 = p1.second;
    double x2 = p2.first, y2 = p2.second;
    return sqrt(square(x1-x2) + square(y1-y2));
}

double dist4(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4)
{
    return dist(p1,p2) + dist(p2,p3) + dist(p3,p4);
}

bool inbound(int x, int y, int n, int m)
{
    return 0 <= x && x <= n && 0 <= y && y <= m;
}

pair<int,int> get_next(pair<int,int> p, int &dir, int n, int m)
{
    int x = p.first, y = p.second;
    int x2, y2;
    switch(dir) {
        case 0:
            x2 = x+1; y2 = y; break;
        case 1:
            x2 = x; y2 = y+1; break;
        case 2:
            x2 = x-1; y2 = y; break;
        case 3:
            x2 = x; y2 = y-1; break;
    }
    if (!inbound(x2, y2, n, m)) {
        dir = (dir+1) % 4;
        return get_next(p, dir, n, m);
    } else return make_pair(x2, y2);
}

bool duplicate(pair<int,int> p1, pair<int,int> p2, pair<int,int> p3, pair<int,int> p4)
{
    if (p1 == p2) return true;
    if (p1 == p3) return true;
    if (p1 == p4) return true;
    if (p2 == p3) return true;
    if (p2 == p4) return true;
    if (p3 == p4) return true;

    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    double length = 0.0;
    pair<int, int> pts[4], p1, p2, p3, p4;
    pts[0] = p1 = p2 = p3 = make_pair(0,0);

    int d2 = 0, d3 = 0;
    do {
        do {
            pair<int,int> corners[4] = {
                make_pair(0,0),
                make_pair(n,0),
                make_pair(n,m),
                make_pair(0,m)};
            for (int x = 0; x < 4; ++x) {
                p4 = corners[x];
                if (duplicate(p1, p2, p3, p4)) continue;
                double cur = dist4(p1, p2, p3, p4);
                if (cur > length) {
                    length = cur;
                    pts[0] = p1; pts[1] = p2; pts[2] = p3; pts[3] = p4;
                }
            }
            p3 = get_next(p3, d3, n, m);
            //cout << p3.first << ' ' << p3.second << endl;
        } while (p3 != make_pair(0,0));
        p2 = get_next(p2, d2, n, m);
    } while (p2 != make_pair(0,0));

    for (int i = 0; i < 4; ++i) {
        cout << pts[i].first << ' ' << pts[i].second << endl;
    }
}
