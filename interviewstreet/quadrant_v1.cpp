// =========================================================
// 
//       Filename:  quadrant.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  01/09/2012 08:45:54 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 01/09/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct node_t {
    int id;
    int begin, end;
    int cnt[4], ops[4];
};

int flip(int quad, int op)
{
    if (op==0) return 3-quad;
    // flip Y
    switch(quad) {
    case 0: return 1;
    case 1: return 0;
    case 2: return 3;
    case 3: return 2;
    }
    return -1;
}

int N; // number of points
int NN; // #nodes in tree
int points[100000+5]; // 0,1,2,3
vector<node_t> vec;

void construct()
{
    NN=2*N-1;    
    vec.resize(NN); //printf("NN %d\n", NN);

    for(int i=0; i<NN; ++i) {
        vec[i].id=i;
        memset(vec[i].cnt, 0, sizeof vec[i].cnt);
        memset(vec[i].ops, -1, sizeof vec[i].ops);
    }
    int n=N; while(n&(n-1)) n&=n-1; n=n*2-1;
    for(int i=n, j=0; i<=2*n; ) {
        if (i<NN) {
            vec[i].begin=vec[i].end=j;
            vec[i].cnt[points[j]]++; 
            j++; i++;
        }
        else {
            int p=(i-1)/2;
            vec[p].begin = vec[p].end = j;
            vec[p].cnt[points[j]]++;
            j++; i+=2;
        }
    }
    for(int i=NN-1; i>0; --i) {
        int p=(i-1)/2;
        if (i&1) vec[p].begin = vec[i].begin;
        else vec[p].end = vec[i].end;
        for(int k=0; k<4; ++k)
            vec[p].cnt[k] += vec[i].cnt[k];
    }
}

void uplocal(int id, int op)
{
    // update ops[]
    int i;
    for(i=0; i<4 && vec[id].ops[i]>=0; ++i)
        ;
    assert(i<4); // must have one vacancy
    if (i==0) vec[id].ops[0]=op;
    else { 
        if (vec[id].ops[i-1]==op) vec[id].ops[i-1]=-1;
        else if (i==3) memset(vec[id].ops, -1, sizeof vec[id].ops);
        else vec[id].ops[i]=op;
    }
    // update cnt[] with op
    int tmp[4]; memcpy(tmp, vec[id].cnt, sizeof tmp);
    for(int i=0; i<4; ++i) {
        vec[id].cnt[i] = tmp[flip(i,op)];
    }        
}

void query(int begin, int end, int id, int ans[])
{
    node_t &node = vec[id];
    // out of range, do nothing
    if (begin > node.end || end < node.begin) return;

    // fully included, return cnt[]
    if (begin<=node.begin && node.end<=end) {
        for(int i=0; i<4; ++i) ans[i] += node.cnt[i];
        return;
    }
    
    // need to split
    // push ops to children
    int ll=id*2+1, rr=id*2+2;
    for(int i=0; i<4 && node.ops[i]>=0; ++i) {
        if (ll<NN) uplocal(ll, node.ops[i]);
        if (rr<NN) uplocal(rr, node.ops[i]);
    }
    memset(node.ops, -1, sizeof node.ops);
    if (ll<NN) query(begin, end, ll, ans);
    if (rr<NN) query(begin, end, rr, ans);
}

void update(int begin, int end, int id, int op)
{
    // out of range, do nothing
    if (begin>vec[id].end || end<vec[id].begin) return;
    // fully included, update cnt[] and propagate to ancestors, update ops[]
    if (begin <= vec[id].begin && vec[id].end <= end) {        
        // update cnt[] with op, propagate to parents        
        // decr from parents
        //for(int p=id; p; p=(p-1)/2) {
        //    for(int i=0; i<4; ++i)
        //        vec[(p-1)/2].cnt[i] -= vec[id].cnt[i];
        //}
        // if we update cnt[] in parent before recurse into children
        // then no need to propagate back to parents
        // update locally
        uplocal(id, op);
        // incr to parents
        //for(int p=id; p; p=(p-1)/2) {
        //    for(int i=0; i<4; ++i)
        //        vec[(p-1)/2].cnt[i] += vec[id].cnt[i];
        //}        
        return;
    }
    // split, first get cnt[] up-to-date for vec[id]
    // then push ops to children
    int tmp[4]={0}, tmp2[4]={0};
    query(begin, end, id, tmp);
    for(int i=0; i<4; ++i) {
        tmp2[i]=tmp[flip(i,op)];
    }
    for(int i=0; i<4; ++i) {
        vec[id].cnt[i]-=tmp[i];
        vec[id].cnt[i]+=tmp2[i];
    }
    int ll=id*2+1, rr=id*2+2;
    for(int i=0; i<4 && vec[id].ops[i]>=0; ++i) {
        if (ll<NN) uplocal(ll, vec[id].ops[i]);
        if (rr<NN) uplocal(rr, vec[id].ops[i]);
    }
    memset(vec[id].ops, -1, sizeof vec[id].ops);
    if (ll<NN) update(begin, end, ll, op);
    if (rr<NN) update(begin, end, rr, op);
}


int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        int x,y; scanf("%d%d", &x, &y);
        if (x>0 && y>0) points[i]=0;
        if (x<0 && y>0) points[i]=1;
        if (x<0 && y<0) points[i]=2;
        if (x>0 && y<0) points[i]=3;
    }

    construct(); //printf("NN %d\n", NN);

    int Q; scanf("%d", &Q);
    for(int q=0; q<Q; ++q) {
        char code[3]; int start, end;
        scanf("%s%d%d", code, &start, &end);
        --start, --end;
        char ch=code[0];
        int ans[4]={0};
        
        switch(ch) {
        case 'C': query(start, end, 0, ans); break;
        case 'X': update(start, end, 0, 0); break;
        case 'Y': update(start, end, 0, 1); break;
        default: assert(false);
        }
        
        //putchar('\n');
        //for(int i=0; i<NN; ++i) { printf("%d: ", i);
            //for(int k=0; k<4; ++k) printf("%d ", vec[i].cnt[k]);
            //putchar('\n');
        //}
        if (ch=='C') {
            for(int i=0; i<4; ++i) {
                if (i) putchar(' ');
                printf("%d", ans[i]);
            }
            putchar('\n');
        }
    }
}

// Time Limit Exceeded
// 10/11 testcases passed
// 25 Point(s) 
//
// use interval tree (augmented binary tree)
// each node is an interval and each has two children with even split of the
// range
//
// observation: consecutive ops can be merged
// if prev=curr, then can remove prev, e.g. XX -> none
// if has 4 diff ops, then all can be removed e.g. XYXY -> none
// so that max number of ops to keep is 3 ops
//
// actually this implementation is wrong
// see quadrant.small
// O(Q*sqrt(N))=10^8.5 is too slow
//
// [lyan@localhost interviewstreet]$ g++ quadrant.cpp 
// quadrant.cpp: In function int main():
// quadrant.cpp:53: warning: unused variable NB
// [lyan@localhost interviewstreet]$ time ./a.out <quadrant.large >my.out 
//
// real 0m28.992s
// user 0m25.784s
// sys  0m0.224s
//
// Quadrant Queries     C++     
// Time Limit Exceeded
// 1/11 testcases passed
// 0.5 Point(s)     View Submission     Processed   2012-01-09 18:41 UTC
// Quadrant Queries     C++     
// Wrong Answer
// 1/11 testcases passed
// 0.5 Point(s)     View Submission     Processed   2012-01-09 17:29 UTC
