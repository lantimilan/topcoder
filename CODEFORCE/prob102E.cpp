// =========================================================
// 
//       Filename:  prob102E.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/16/2011 12:53:28 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 09/16/2011, LI YAN
// 
// =========================================================

#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

typedef pair<int,int> pii; // x,y

int gcd(int a, int b)
{
    if (a<b) swap(a,b);
    if (a%b==0) return b;
    return gcd(b,a%b);
}

int main()
{
    pii A,B,C;
    cin >> A.first >> A.second;
    cin >> B.first >> B.second;
    cin >> C.first >> C.second;

    bool good=false;
    for(int i=0; i<4; ++i) {
        pii D; 
        D.first= B.first-A.first;
        D.second= B.second-A.second;
        int x=D.first, y=D.second;
        int cx=C.first, cy=C.second;

        long long det=(long long)cx*cx+(long long)cy*cy;
        if (det==0) {
            if (x==0 && y==0) { good=true; break; }
        }
        else {
            if (((long long)cx*x+(long long)cy*y)%det==0 && 
                ((long long)-cy*x+(long long)cx*y)%det==0)  // WA here due to integer overflow
            { good=true; break; }
        }

        pii newA=pii(-A.second,A.first);
        A=newA;
    }
    if (good) cout << "YES" << endl;
    else cout << "NO" << endl;
}

// 705791   Sep 17, 2011 1:30:34 AM     lantimilan  E - Vectors     GNU C++
// Accepted     30 ms   1400 KB
// 705786   Sep 17, 2011 1:24:40 AM     lantimilan  E - Vectors     GNU C++
// Wrong answer on test 15  30 ms   1400 KB 
// WA due to integer overflow 
//
// the sum reachable from A by add C and rotate is of the form
// A[i] + x1*C1 + x2*C2 + x3*C3 + x4*C4
// where A[1],A[2],A[3],A[4] are obtained by rotating A
// notice that A appears only once in this sum
//
// Now we can try the 4 possible A[i]
// And then we have D = B - A[i]
// and D = x1*C1 + x2*C2 + x3*C3 + x4*C4 for nonnegative integers
// x1,x2,x3,x4
//
// Let D=(x,y) and expand C1,C2,C3,C4
// we have 
// x=(x1-x3)*cx - (x2-x4)*cy
// y=(x2-x4)*cx + (x1-x3)*cy
//
// Let z1=x1-x3, z2=x2-x4, we have nonnegative integer solution 
// x1,x2,x3,x4 iff we have any integer solution z1,z2
//
// So we are to find when 
// x=z1*cx - z2*cy
// y=z2*cx + z1*cy
// has integer solution
//
// for this to have a solution, we have the solution being
// inv(| cx -cy |) |x|  = 1/det ( cx cy ) (x)
//    (| cy  cx |) |y|          (-cy cx ) (y)
//
// if det=0, then row (cx, -cy) is a multiple of row(cy,cx)
//     this implies cx/cy=-cy/cx, which further implies cx=cy=0
//     therefore we need x=y=0 to have a solution
// else (x*cx+y*cy) and (x*-cy+y*cx) have to be divisible by det
//
//
