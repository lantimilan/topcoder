// =========================================================
// 
//       Filename:  prob77E.cpp
// 
//    Description:  E. Martian Food
// 
//        Version:  1.0
//        Created:  04/20/2011 09:32:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 04/20/2011, LI YAN
// 
// =========================================================

// computational geometry
// primitives
//
#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef pair<int,int> PI;

#define INF (1<<29)
#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define ALL(x) x.begin(), x.end()
#define PB push_back
#define MP make_pair

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

Point operator*(double s, Point p)
{
    return Point(s*p.x,s*p.y);
}

bool operator<(Point p1, Point p2)
{ return p1.x < p2.x || (p1.x==p2.x && p1.y < p2.y); }

bool operator==(Point p1, Point p2)
{ return fabs(p1.x-p2.x)<=EPS && fabs(p1.y-p2.y)<=EPS; }

bool operator!=(Point p1, Point p2)
{ return !(p1==p2); }

ostream& operator<<(ostream &os, Point p) 
{
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

PType dot(Point p1, Point p2)
{ return p1.x * p2.x + p1.y * p2.y; }

PType det(Point p1, Point p2) // cross product
{ return p1.x * p2.y - p1.y * p2.x; }

Point rotate(Point p, double t)
{
    return Point(p.x*cos(t)-p.y*sin(t), p.y*cos(t)+p.x*sin(t));
}

inline double norm2(Point p)
{ return (p.x*p.x + p.y*p.y); }

inline double norm(Point p)
{ return sqrt(norm2(p)); }

inline double dist2(Point p1, Point p2)
{ return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y); }

inline double dist(Point p1, Point p2)
{ return sqrt(dist2(p1,p2)); }

// distance from pt to line (p1,p2)
// always >= 0
double linePtDist(Point p1, Point p2, Point pt)
{
    Point v1 = p1-pt, v2=p2-pt;
    double area = det(v1,v2);
    return fabs(area) / dist(p1,p2);
}

// returns true if pt is in segment(p1,p2)
// assumes pt in line(p1,p2)
bool ptInRange(Point p1, Point p2, Point pt)
{
    double eps = EPS*10;
    bool good = (min(p1.x,p2.x)-eps <= pt.x) && (pt.x <= max(p1.x,p2.x)+eps) &&
        (min(p1.y,p2.y)-eps <= pt.y) && (pt.y <= max(p1.y,p2.y)+eps);
    return good;
}

bool collinear(Point p1, Point p2, Point p3)
{ return linePtDist(p1,p2,p3) <= EPS; }

bool ptInSegment(Point p1, Point p2, Point pt)
{
    return linePtDist(p1,p2,pt) <= EPS && ptInRange(p1,p2,pt);
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
bool lineIntersect(double A1, double B1, double C1,
    double A2, double B2, double C2, Point &pt)
{
    double det = A1*B2 - A2*B1;
    if (fabs(det) < EPS) { 
        //cerr << "Two lines parallel or coincide, no intersection\n";
        return false;
    } else {
        pt.x = 1.0/det*(B2*C1-B1*C2);
        pt.y = 1.0/det*(A1*C2-A2*C1);
        return true;
    }
}

// convert line (p1,p2) to Ax+By=C
void pt2line(Point p1, Point p2, double &A, double &B, double &C)
{ A = (p2.y-p1.y); B = (p1.x-p2.x); C = A*p1.x+B*p1.y; }

// returns true if segment (p1,p2) intersects (p3,p4)
bool segmentIntersect(Point p1, Point p2, Point p3, Point p4)
{
    double A1,B1,C1; pt2line(p1,p2,A1,B1,C1);
    double A2,B2,C2; pt2line(p3,p4,A2,B2,C2);
    Point pt;
    if (!lineIntersect(A1,B1,C1,A2,B2,C2,pt)) return false;
    return ptInRange(p1,p2,pt) && ptInRange(p3,p4,pt);
}

// which side does pt lies in line(p1,p2)
// returns +1 if pt on the left of p1p2
//          0 if pt is on p1p2
//         -1 if pt is on the right of p1p2
int ptLineSide(Point p1, Point p2, Point pt)
{
    Point v1 = p2-p1, v2 = pt-p1;
    double val = det(v1,v2)/(norm(v1)*norm(v2)); // relative error
    if (fabs(val) <= EPS) return 0;
    else if (val > 0) return +1;
    else return -1;
}

// returns true if segment (p1,p2) intersects (p3,p4)
// use two points on two sides of the line
bool isSegIntersect(Point p1, Point p2, Point p3, Point p4)
{
    // TODO: need to check if all 4 points are collinear
    return (ptLineSide(p1,p2,p3)*ptLineSide(p1,p2,p4) <= 0 &&
        ptLineSide(p3,p4,p1)*ptLineSide(p3,p4,p2) <= 0);
}

double max3(double a, double b, double c)
{ return max(a,max(b,c)); }
double min3(double a, double b, double c)
{ return min(a,min(b,c)); }
// return the center of a circle that passes
// three points in pts[3]
Point circumcenter(Point pts[])
{
    //for(int i=0; i < 3; ++i) { cout << pts[i] << " "; } cout << endl;
    double x1 = pts[0].x, y1 = pts[0].y;
    double x2 = pts[1].x, y2 = pts[1].y;
    double x3 = pts[2].x, y3 = pts[2].y;

    if (collinear(pts[0],pts[1],pts[2]))
    {
        double xc = (min3(x1,x2,x3) + max3(x1,x2,x3))/2.0;
        double yc = (min3(y1,y2,y3) + max3(y1,y2,y3))/2.0;
        return Point(xc,yc);
    }
    // line (x1,y1) to (x2,y2) and bisector
    double A1 = y2-y1, B1 = x1-x2; // C1 = A1*x1+B1*y1;
    double D1 = -B1, E1 = A1, F1 = D1*(x1+x2)/2.0 + E1*(y1+y2)/2.0;
    // line (x2,y2) to (x3,y3) and bisector
    double A2 = y3-y2, B2 = x2-x3; // C2 = A2*x2+B2*y2;
    //cout << A2 << " " << B2 << endl;
    double D2 = -B2, E2 = A2, F2 = D2*(x2+x3)/2.0 + E2*(y2+y3)/2.0;

    Point pt;
    bool isinter = lineIntersect(D1,E1,F1,D2,E2,F2,pt);
    assert(isinter);
    return pt;
}

// return signed area of polygon
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

vector<Point> convex_hull(vector<Point> pa)
{
    //cout << "convex_hull\n";
    int n = pa.size();
    if (n < 2) return pa;
    vector<Point> hull(2*n); // npoints <= pa.size()+1 ?

    sort(pa.begin(), pa.end());

    // lower half chain
    int k=0;
    for(int i=0; i < n; hull[k++] = pa[i++])
        while(k > 1 && det(hull[k-1]-hull[k-2], pa[i]-hull[k-2]) <= 0) k--;
    // upper half chain
    for(int i=n-2, t=k; i >= 0; hull[k++] = pa[i--])
        while(k > t && det(hull[k-1] - hull[k-2], pa[i]-hull[k-2]) <= 0) k--;

    k--;
    vector<Point> ret(k);
    copy(hull.begin(), hull.begin()+k, ret.begin());
    return ret;
}

// returns
// +1 if inside
// -1 if outside
// 0  if on boundary
int ptInPolygon(const vector<Point> &pts, Point pt)
{
    // test inside or outside using ray
    Point ptout(INT_MAX,INT_MAX);
    //cout << "pt " << pt << " " << "ptout " << ptout << endl;
    int cnt=0, N=pts.size();
    for(int i=0; i<N; ++i)
    { 
        Point p1=pts[i], p2=pts[(i+1)%N];
        //cout << p1 << " " << p2 << endl;
        if (ptInSegment(p1,p2,pt)) return 0;

        if (segmentIntersect(pt,ptout,p1,p2) !=
            isSegIntersect(pt,ptout,p1,p2))
        { cout << pt << " " << ptout << " " << p1 << " " << p2 << endl;
            abort(); }
        if (segmentIntersect(pt,ptout,p1,p2)) { 
        //if (isSegIntersect(pt,ptout,p1,p2)) { 
            //cout << "segment " << p1 << " " << p2 << endl;
            if (ptInSegment(pt,ptout,p1) && ptInSegment(pt,ptout,p2))
            { /* cerr << "seg in seg, do nothing\n";  do nothing */ }
            else if (ptInSegment(pt,ptout,p2))
            {
                // if both p1 and p3 on same side, do nothing
                // else cnt++
                Point p3 = pts[(i+2)%N];
                double left1, left2;
                left1 = det(p1-pt,ptout-pt);
                left2 = det(p3-pt,ptout-pt);
                if (left1*left2 < 0) cnt++;
            }
            else if (ptInSegment(pt,ptout,p1))
            { /* do nothing */ }
            else { cnt++; }
            //cout << cnt << endl;
        }
    }
    //cout << "cnt " << cnt << endl;
    if (cnt&1) return +1;
    else return -1;
}

class PointInPolygon
{ 
public: 
    string testPoint(vector <string> ver, int testX, int testY) 
    { 
        string in="INTERIOR", out="EXTERIOR", bound="BOUNDARY";
        int N = ver.size(); Point pt(testX,testY);
        vector<Point> pts;
        for(int i=0; i<N; ++i)
        {
            istringstream ss(ver[i]);
            int x,y; ss >> x >> y; pts.push_back(Point(x,y));
        }
        switch(ptInPolygon(pts,pt))
        {
        case +1: return in;
        case -1: return out;
        case  0: return bound;
        }
        return out;
    } 
}; 

class Point3D
{
public:
    double x, y, z;
    Point3D() { x=y=z=0.0; }
    Point3D(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
};

Point3D operator-(Point3D p1, Point3D p2) { return Point3D(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z); }
ostream& operator<<(ostream &os, Point3D p)
{ return os << "(" << p.x << "," << p.y << "," << p.z << ")"; }

bool operator==(Point3D p1, Point3D p2)
{ return (fabs(p1.x-p2.x)<=EPS && fabs(p1.y-p2.y)<=EPS && fabs(p1.z-p2.z)<=EPS); }
bool operator!=(Point3D p1, Point3D p2)
{ return !(p1==p2); }

double sqr(double x) { return x*x; }

double norm2(Point3D p) { return sqr(p.x)+sqr(p.y)+sqr(p.z); }
double norm(Point3D p) { return sqrt(norm2(p)); }

double dist2(Point3D p1, Point3D p2)
{ return (sqr(p1.x-p2.x) + sqr(p1.y-p2.y) + sqr(p1.z-p2.z)); }
double dist(Point3D p1, Point3D p2)
{ return sqrt(dist2(p1,p2)); }

// compute surface distance of two points on a sphere
double balldist(double lat1, double lng1, double lat2, double lng2, double R)
{
    double dlat = lat2-lat1, dlng = lng2-lng1;
    double a = sqr(sin(dlat/2))+cos(lat1)*cos(lat2)*sqr(sin(dlng/2));
    double c = 2*atan2(sqrt(a), sqrt(1-a));
    return R*c;
}

double dot(Point3D p1, Point3D p2)
{ return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z; }

Point3D cross(Point3D p1, Point3D p2)
{ 
    double x = p1.y*p2.z - p1.z*p2.y;
    double y = -(p1.x*p2.z - p1.z*p2.x);
    double z = p1.x*p2.y - p2.x*p1.y;
    return Point3D(x,y,z);
}

// return dist from pt to line (p1,p2)
double ptLineDist(Point3D p1, Point3D p2, Point3D pt)
{
    double area = norm(cross(p1-pt,p2-pt));
    if (p1==p2) return dist(p1,pt);
    else return area/dist(p1,p2);
}

// careful when passing params
void XYZconvert(double lat, double lng, double alt, Point3D &pt)
{
    const double PI = acos(-1.0);
    pt.x = cos(lng/180*PI)*cos(lat/180*PI)*alt;
    pt.y = sin(lng/180*PI)*cos(lat/180*PI)*alt;
    pt.z = sin(lat/180*PI)*alt;
}

// return surface distance of two points on a sphere
// use great circle method
double balldist(Point3D p1, Point3D p2, double R)
{
    double ang = acos(dot(p1,p2)/(norm(p1)*norm(p2)));
    return ang*R;
}

// return surface distance of two points on a sphere
// use formula from wiki
double balldist2(double lat1, double lng1, double lat2, double lng2, double R)
{
    double dlat = lat2-lat1, dlng = lng2-lng1;
    double a = sqr(sin(dlat/2))+cos(lat1)*cos(lat2)*sqr(sin(dlng/2));
    double c = 2*atan2(sqrt(a), sqrt(1-a));
    return R*c;
}

void solve()
{
    double R, r1, r2, res; int k; cin >> R >> r1 >> k;
    r2 = R-r1;

    Point c1=Point(-r2,0), c2=Point(r1,0),c3;
    for(int i=0; i<k; ++i)
    {
    double d=0, lo=0, hi=r2, r3=0; //cout << "lo " << lo << " " << hi << endl;
    do
    {
        r3 = (lo+hi)/2;
        double a=r1+r3, b=r1+r2, c=r2+r3;
        double theta = acos((a*a+b*b-c*c)/(2*a*b));
        c3 = a/b*rotate(c2-c1,theta)+c1;
        d = dist(c3,Point(0,0));
        //cout << c3 << "\t" << r3 << "\t" << d << endl;
        if (fabs(d+r3-R) < 1.0e-9) break;
        else if (d+r3 > R) { hi=r3; }
        else if (d+r3 < R) { lo=r3; }
    } while(1);
    //cout << "found " << c3 << " " << r3 << endl;
    res = r2 = r3; c2 = c3;
    }
    cout << fixed << setprecision(10) << res << endl;
}
int main()
{
    int T; cin >> T;
    for(int t=0; t<T; ++t) solve();
}

// binary search to find r3
// will it TLE?
// EPS=1.0e-6 did get TLE
// 404269        Apr 21, 2011 10:19:46 AM   lantimilan        77E - Martian Food
// GNU C++       Time limit exceeded on test 6       2000 ms     1400 KB 
//
// is the precision good enough for 1.0e-6?
