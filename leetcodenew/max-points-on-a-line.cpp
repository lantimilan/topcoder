// max-points-on-a-line.cpp
//
// A * x + B * y = C
// given two points (x1, y1) and (x2, y2)
//
/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 *
 * assume all points are distinct
 *
 * line representation: A * x + B * y = C
 * since a line passing (x1,y1) and (x2,y2) can be represented as
 * y = (y2-y1)/(x2-x1) * x + b
 * we have A = y2-y1, B = -(x2-x1), and use (x1,y1) we get C
 * we reduce each triple (A,B,C) to its canonical form
 * that is, A, B, C are reduced so that gcd = 1
 * and A >= 0
 * if (A == 0) then B >= 0
 * we cannot have A==0 and B==0 if (x1,y1) and (x2,y2) are two distinct points
 */
class Solution {
public:
    typedef pair<int,int> pii;
    typedef pair<pii, int> triple;

    int maxPoints(vector<Point> &points) {
        map<triple, set<pii> > line_cnt;
        for (int i = 0; i < points.size(); ++i)
        for (int j = i+1; j < points.size(); ++j) {
            Point p1, p2;
            p1 = points[i]; p2 = points[j];
            if (p1.x != p2.x || p1.y != p2.y) {
                triple line = pt2line(p1, p2);
                line_cnt[line].insert(pt2pair(p1));
                line_cnt[line].insert(pt2pair(p2));
            }
        }
        if (line_cnt.empty()) return points.size();

        map<pii, int> point_cnt;
        for (int i = 0; i < points.size(); ++i) {
            point_cnt[pt2pair(points[i])]++;
        }
        int maxcnt = 0;
        map<triple,set<pii> >::const_iterator mapit;
        for (mapit = line_cnt.begin(); mapit != line_cnt.end(); ++mapit) {
            int cur = 0;
            set<pii>::iterator sit;
            for (sit = mapit->second.begin(); sit != mapit->second.end(); ++sit) {
                pii pt = *sit;
                cur += point_cnt[pt];
            }
            maxcnt = max(maxcnt, cur);
        }
        return maxcnt;
    }
private:
    pii pt2pair(Point p) {  // we need this because Point may not implement less operator
        return make_pair(p.x, p.y);
    }

    triple pt2line(Point p1, Point p2) {
        int x1 = p1.x, y1 = p1.y;
        int x2 = p2.x, y2 = p2.y;
        int A, B, C;
        A = y2 - y1; B = x1 - x2; C = A * x1 + B * y1;
        int g = gcd(A, B);
        g = gcd(g, C);
        A /= g; B /= g; C /=g;
        if (A < 0) { A = -A; B = -B; C = -C; }
        else {
            if (A == 0) {
                if (B < 0) { B = -B; C = -C; }
            }
        }
        triple t = make_pair(make_pair(A, B), C);
        return t;
    }

    int gcd(int a, int b) {
        if (b == 0) return a;
        else return gcd(b, a%b);
    }
};

