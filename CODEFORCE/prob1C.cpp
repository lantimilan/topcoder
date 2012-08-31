// =========================================================
// 
//       Filename:  prob1C.cpp
// 
//    Description:  C. Ancient Berland Circus
// 
//        Version:  1.0
//        Created:  03/15/2011 05:27:44 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 03/15/2011, LI YAN
// 
// =========================================================

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const double EPS = 1.0e-9;
typedef double PType;
class Point
{
public:
    PType x, y;
    Point() : x(0), y(0) {}
    Point(PType xx, PType yy) : x(xx), y(yy) {}
};

Point operator+(Point p1, Point p2)
{ return Point(p1.x + p2.x, p1.y + p2.y); }

Point operator-(Point p1, Point p2)
{ return Point(p1.x - p2.x, p1.y - p2.y); }

Point operator*(Point p1, Point p2)
{
    double x = p1.x*p2.x - p1.y*p2.y;
    double y = p1.x*p2.y + p1.y*p2.x;
    return Point(x,y);
}

PType dot(Point p1, Point p2)
{ return p1.x * p2.x + p1.y * p2.y; }

PType det(Point p1, Point p2) // cross product
{ return p1.x * p2.y - p1.y * p2.x; }

inline double norm(Point p)
{ return sqrt(p.x*p.x + p.y*p.y); }

inline double norm2(Point p)
{ return (p.x*p.x + p.y*p.y); }

inline double dist2(Point p1, Point p2)
{ return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y); }

bool operator<(Point p1, Point p2)
{
    return p1.x < p2.x || (p1.x==p2.x && p1.y < p2.y);
}

ostream& operator<<(ostream &os, Point p) 
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

// intersect two lines
// A1*x + B1*y = C1
// A2*x + B2*y = C2
//
// careful when intersecting line segments
// (x1,y1) (x2,y2)
// (x3,y3) (x4,y4)
// intersection (x,y) has to satisfy
// min(x1,x2) <= x <= max(x1,x2)
// ...
// watch for floating point precision issue
Point line_inter(double A1, double B1, double C1,
    double A2, double B2, double C2)
{
    double det = A1*B2 - A2*B1;
    if (fabs(det) < EPS) { 
        assert(false);
        cerr << "Two lines parallel or coincide, no intersection\n";
        return Point(0,0); 
    } else {
        double x = 1.0/det*(B2*C1-B1*C2);
        double y = 1.0/det*(A1*C2-A2*C1);
        return Point(x,y);
    }
}

// return the center of a circle that passes
// three points in pts[3]
Point circumcenter(Point pts[])
{
    //for(int i=0; i < 3; ++i) { cout << pts[i] << " "; } cout << endl;
    double x1 = pts[0].x, y1 = pts[0].y;
    double x2 = pts[1].x, y2 = pts[1].y;
    double x3 = pts[2].x, y3 = pts[2].y;

    // line (x1,y1) to (x2,y2) and bisector
    double A1 = y2-y1, B1 = x1-x2; // C1 = A1*x1+B1*y1;
    //cout << A1 << " " << B1 << endl;
    double D1 = -B1, E1 = A1, F1 = D1*(x1+x2)/2.0 + E1*(y1+y2)/2.0;
    // line (x2,y2) to (x3,y3) and bisector
    double A2 = y3-y2, B2 = x2-x3; // C2 = A2*x2+B2*y2;
    //cout << A2 << " " << B2 << endl;
    double D2 = -B2, E2 = A2, F2 = D2*(x2+x3)/2.0 + E2*(y2+y3)/2.0;

    //cout << D1 << " " << E1 << " " << F1 << " " << D2 << " " << E2 << " " << F2 << endl;
    return line_inter(D1,E1,F1,D2,E2,F2);
}

double area(const vector<Point> &pa)
{
    int n = pa.size();
    double ret = 0.0;
    for(int i=0; i < n; i++)
    {
        ret += det(pa[i], pa[(i+1)%n]);
    }
    return ret/2.0;
}


void solve()
{
    Point pts[3];
    for(int i=0; i < 3; ++i)
        cin >> pts[i].x >> pts[i].y;

    Point center = circumcenter(pts); //cout << "center " << center << endl;
    double R2 = dist2(center, pts[0]);
    int n;
    for(n=3; n <= 100; ++n)
    {
        bool hit1=false, hit2=false;
        Point v = pts[0] - center;
        double theta=2*acos(-1.0)/n; //cout << theta*180/acos(-1.0) << endl;
        for(int i=1; i<n; ++i)
        {
            Point newpt = center + v*Point(cos(theta*i),sin(theta*i));
            //cout << n << " " << newpt << endl;
            double err = 1.0e-4;
            if (fabs(newpt.x-pts[1].x) <= err && fabs(newpt.y-pts[1].y) <= err) hit1 = true;
            if (fabs(newpt.x-pts[2].x) <= err && fabs(newpt.y-pts[2].y) <= err) hit2 = true;
        }
        if (hit1 && hit2) break;
    }
    //cerr << n << endl;
    double area = n*R2*sin(2*acos(-1.0)/n)/2.0;
    cout << fixed << setprecision(9) << area << endl;
}

int main()
{
    //for(int i=0; i < 2; i++)
    solve();
}

/* **********************
 * after read
 * http://algorithack.blogspot.com/2011/02/codeforces-1-c-ancient-berland-circus.html
 * change line 155 double err=1.0e-6 to err=1.0e-4, AC. But how do you analyze
 * the error?
 *
 * 338214   Mar 16, 2011 5:43:42 AM     lantimilan  1C - Ancient Berland Circus
 * GNU C++  Accepted    30 ms   1400 KB
 *
 * 338211   Mar 16, 2011 5:39:56 AM     lantimilan  1C - Ancient Berland Circus
 * GNU C++  Wrong answer on test 8  30 ms   1400 KB
 *
 * 338196        Mar 16, 2011 4:10:54 AM    lantimilan        1C - Ancient
 * Berland Circus        GNU C++     Wrong answer on test 1      10 ms
 * 1400 KB 
 * */
