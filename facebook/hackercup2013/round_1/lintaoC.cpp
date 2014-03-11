// =========================================================
//
//       Filename:  Dead Pixels
//
//    Description:
//
//        Version:  1.0
//        Created:  02/02/2013
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Tao Lin, tlin005@gmail.com
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 02/02/2013
//
// =========================================================

#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

#define MAXLINE 103

struct pts {
    int x;
    int y;
} ;
struct recs {
    pts pt1;
    pts pt2;
} ;

struct segment{
    double ly, hy, x;
    int cover;
    segment(){}
    segment(double a,double b,double c,int d):ly(a),hy(b),x(c),cover(d){}
    bool operator < (const segment& cmp)const{
        return x<cmp.x;
    }
};

struct node{
    int left, right;
    double len;
    int cover;
};

#define MAXN 2000000
node tree[MAXN*4+4];
int y[MAXN*2+1];
segment seg[MAXN*2+1];

void Build(node tree[], int u, int l, int r)
{
    tree[u].left = l;
    tree[u].right = r;
    tree[u].cover = 0;
    tree[u].len = 0;

    if(l+1 == r)
        return;

    int mid = (l+r)>>1;
    Build(tree, u*2, l, mid);
    Build(tree, u*2+1, mid, r);
}

void PushUp(node tree[], int y[], int u)
{
    if (tree[u].cover > 0)
        tree[u].len = y[tree[u].right] - y[tree[u].left];
    else if (tree[u].left+1 == tree[u].right)
        tree[u].len = 0;
    else
        tree[u].len = tree[u*2].len + tree[u*2+1].len;
}

void Update(node tree[], int y[], int u, int l, int r, int cover)
{
    if (r < tree[u].left || tree[u].right < l)
        return;

    if (l <= tree[u].left && tree[u].right <= r)
    {
        tree[u].cover += cover;
    }
    else {
        if (l <= tree[u*2].right)
            Update(tree, y, u*2, l, r, cover);
        if (r >= tree[u*2+1].left)
            Update(tree, y, u*2+1, l, r, cover);
    }

    PushUp(tree, y, u);
}

unsigned long long area(vector< recs > rec)
{
    unsigned long long int result = 0;

    unsigned int n = rec.size();
    unsigned int cnt = 0;
    for(unsigned int i = 0; i < n; ++i){
        y[cnt] = rec[i].pt1.y;
        seg[cnt++] = segment(rec[i].pt1.y, rec[i].pt2.y, rec[i].pt1.x, 1);
        y[cnt] = rec[i].pt2.y;
        seg[cnt++] = segment(rec[i].pt1.y, rec[i].pt2.y, rec[i].pt2.x, -1);
    }

    sort(y, y+cnt);
    sort(seg, seg+cnt);

    int num = unique(y, y+cnt) - y;
    Build(tree, 1, 0, num-1);

    for (unsigned int i = 0; i < 2*n-1; ++i)
    {
        int ll = lower_bound(y, y+num, seg[i].ly) - y;
        int rr = lower_bound(y, y+num, seg[i].hy) - y;

        Update(tree, y, 1, ll, rr, seg[i].cover);
        result += tree[1].len*(seg[i+1].x-seg[i].x);
    }

    return result;
}

unsigned long long int solve(int W, int H, int P, int Q, int N, vector< pts > dead)
{
    unsigned long long int result = 0;

    vector< recs > dzone (N+2);
    // corners
    dzone[0].pt1.x = W-P+1;  dzone[0].pt1.y = 0;  dzone[0].pt2.x = W;  dzone[0].pt2.y = H;
    dzone[1].pt1.x = 0;  dzone[1].pt1.y = H-Q+1;  dzone[1].pt2.x = W;  dzone[1].pt2.y = H;
    // dead pixels
    for (int i = 0; i < N; ++i)
    {
        dzone[i+2].pt1.x = max(0, dead[i].x - P + 1);
        dzone[i+2].pt1.y = max(0, dead[i].y - Q + 1);
        dzone[i+2].pt2.x = min(W+1, dead[i].x + 1);
        dzone[i+2].pt2.y = min(H+1, dead[i].y + 1);
    }

    result = W*H - area(dzone);
    return result;
}

int main()
{
    unsigned int case_no;
    unsigned long long int result;

    unsigned int W;
    unsigned int H;
    unsigned int P;
    unsigned int Q;

    unsigned int N;
    unsigned int X;
    unsigned int Y;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;


    // load input
    cin >> case_no;

    for (unsigned int t = 0; t < case_no; ++t)
    {

        cin >> W >> H >> P >> Q;
        cin >> N;
        cin >> X >> Y >> a >> b >> c >> d;
        // sove problem

        vector< pts > dead (1000002);
        dead[0].x = X;
        dead[0].y = Y;
        for (unsigned int i = 1; i< N; ++i)
        {
            //pts foo;
            dead[i].x = (dead[i-1].x * a + dead[i-1].y * b + 1) % W;
            dead[i].y = (dead[i-1].x * c + dead[i-1].y * d + 1) % H;
        }

        result = solve(W, H, P, Q, N, dead);

        cout << "Case #" << t+1 << ": ";
        cout << result << endl;
    }

    return 0;

}
