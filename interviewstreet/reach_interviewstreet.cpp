// =========================================================
// 
//       Filename:  address.cpp
// 
//    Description:  interviewstreet Summer Games
//        Challenges / Reach InterviewStreet
// 
//        Version:  1.0
//        Created:  06/18/2012 06:25:59 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 06/18/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

typedef pair<int,int> pii;

int N, M;
bool vis[10][10];
vector<vector<pii> > ans;

const string mat[] = {
    "A..5PD",
    "TVDASO",
    "C.AM.4",
    "3S..N.",
    "WI5.7E",
    "1.F429",
};

bool inbound(int i, int j)
{
    return 0<=i && i<N && 0<=j && j<M;
}

void print(const vector<pii> &list)
{
    for(int i=0; i<int(list.size()); ++i)
        cout << '(' << list[i].first << ',' 
            << list[i].second << ')' << ' ';
    cout << endl;
    for(int i=0; i<int(list.size()); ++i)
        cout << mat[list[i].first][list[i].second];
    cout << endl;
}


void pt2line(double x1, double y1, double x2, double y2, double &A, double &B, double &C)
{
    A=(y2-y1); B=(x1-x2); C=A*x1+B*y1;
}

bool iscross(pii p1, pii p2, pii p3, pii p4)
{
    double x1, x2, x3, x4;
    double y1, y2, y3, y4;
    double A1, B1, C1;
    double A2, B2, C2;
    double D1, D2, D3, D4;

    x1=p1.first + 0.5;
    y1=p1.second+ 0.5;
    x2=p2.first + 0.5;
    y2=p2.second+ 0.5;
    x3=p3.first + 0.5;
    y3=p3.second+ 0.5;
    x4=p4.first + 0.5;
    y4=p4.second+ 0.5;
    pt2line(x1,y1,x2,y2,A1,B1,C1);
    pt2line(x3,y3,x4,y4,A2,B2,C2);

    D1 = A1*x3 + B1*y3 -C1;
    D2 = A1*x4 + B1*y4 -C1;
    D3 = A2*x1 + B2*y1 -C2;
    D4 = A2*x2 + B2*y2 -C2;

    const double EPS=1.0e-9;
    return D1*D2<=EPS && D3*D4<=EPS;
}

void dfs(int i, int j, vector<pii> pre)
{
    /*
    if (mat[i][j]=='.' && !pre.empty() && pre[pre.size()-1]=='.') return;
    if (!pre.empty()) {
        char ch = pre[pre.size()-1];
        if (isdigit(ch) && mat[i][j]!='.' && !isdigit(mat[i][j])) return;
        if (!isdigit(ch) && ch!='.' && isdigit(mat[i][j])) return;
    }  */
    if (vis[i][j]) { //{ print(pre); return; }
        if (ans.empty()) ans.push_back(pre);
        else if (ans[0].size() < pre.size()) { ans.clear(); ans.push_back(pre); }
        else if (ans[0].size() == pre.size()) { ans.push_back(pre); }
    }
    if (pre.size() >=3U) {
        pii p1, p2, p3, p4;
        p3=pre.back(); p4=pii(i,j);
        int n=pre.size();
        for(int i=0; i+1<n-1; ++i) {
            p1=pre[i]; p2=pre[i+1];
            if (iscross(p1,p2,p3,p4)) return;
        }
    }
    vis[i][j]=true;
    int dx[] = {-1,+1,-1,+1,-2,+2,-2,+2};
    int dy[] = {-2,-2,+2,+2,-1,-1,+1,+1};
    for(int x=0; x<8; ++x) {
        int i2, j2;
        i2=i+dx[x]; j2=j+dy[x];
        if (inbound(i2,j2)) {
            pre.push_back(pii(i,j));
            dfs(i2, j2, pre);
            pre.pop_back();
        }
    }
    vis[i][j]=false;
}

int main()
{
    N = sizeof(mat)/sizeof(mat[0]);
    M = mat[0].length();
    memset(vis, 0, sizeof vis);
    dfs(N-1,0,vector<pii>());
    for(int i=0; i<int(ans.size()); ++i)
        print(ans[i]);
}

// answer is
// 152.E.DANA.ST.MV.
// Reach InterviewStreet    python  2012-06-23 18:01:10     Processed   Accepted
// Score: 20
//  View Details
