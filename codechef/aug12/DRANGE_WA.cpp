// =========================================================
// 
//       Filename:  DRANGE.cpp
// 
//    Description:  http://www.codechef.com/AUG12/problems/DRANGE
// 
//        Version:  1.0
//        Created:  08/03/2012 09:50:53 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 08/03/2012, LI YAN
// 
// =========================================================

// segment tree
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;
 
typedef pair<int,int> pii;
 
struct node_t {
  int start, end;
  int min, max;
  int extra;
};
 
#define MAX (1<<22)
int val[MAX];
int N, M;
 
struct segment_tree {
  node_t nodes[MAX];
  int size;
 
  segment_tree() {}

  segment_tree(int n)
  {
    size=n;
    init(0, 0, n);
  }
 
  void init(int id, int l, int r)
  {
    assert(l<r);
    nodes[id].start = l;
    nodes[id].end = r;
    nodes[id].extra = 0;
    if (l+1 == r) {
      nodes[id].min = nodes[id].max = val[l];
    }
    else {
      int m = (l+r)/2;
      int c1, c2;
      c1 = 2*id+1; c2 = 2*id+2;
      init(c1, l, m);
      init(c2, m, r);
      int a, b;
      a = min(nodes[c1].min, nodes[c2].min);
      b = max(nodes[c1].max, nodes[c2].max);
      nodes[id].min = a;
      nodes[id].max = b;
    }
  }
 
  pii query(int id, int l, int r) {
    assert(l<r);
    int start, end;
    start = nodes[id].start;
    end = nodes[id].end;
    if (start == l && end == r)
      return pii(nodes[id].min, nodes[id].max);
    int c1, c2;
    int m = (start+end)/2;
    c1 = 2*id+1; c2 = 2*id+2;
    update(c1, start, m, nodes[id].extra);
    update(c2, m, end, nodes[id].extra);
    nodes[id].extra = 0;
    if (m>=r) {
      return query(c1, l, r);
    }
    else if (l>=m) {
      return query(c2, l, r);
    }
    else {
      pii p1, p2;
      p1 = query(c1, l, m);
      p2 = query(c2, m, r);
      return pii(min(p1.first, p2.first), max(p1.second, p2.second));
    }
  }
 
  void update(int id, int l, int r, int k) // add k to val[l..r-1]
  {
    assert(l<r);
    int start, end;
    start = nodes[id].start; end = nodes[id].end;
    if (l==start && r==end) {
      nodes[id].min += k;
      nodes[id].max += k;
      nodes[id].extra +=k;
      return;
    }
    int c1, c2;
    int m = (start+end)/2;
    pii p;
    c1 = 2*id+1; c2 = 2*id+2;
    update(c1, start, m, nodes[id].extra);
    update(c2, m, end, nodes[id].extra);
    nodes[id].extra = 0;
    if (m>=r) { // update left c1
      update(c1, l, r, k);
    }
    else if (l>=m) { // update right c2
      update(c2, l, r, k);
    }
    else { // update c1 and c2
      update(c1, l, m, k);
      update(c2, m, r, k);
    }
    nodes[id].min = min(nodes[c1].min, nodes[c2].min);
    nodes[id].max = max(nodes[c2].max, nodes[c2].max);
  }
};

segment_tree st;

int main()
{
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &N, &M);
        for(int i=0; i<N; ++i) {
            val[i] = i+1;
        }
        st.size = N; st.init(0, 0, N);
        for(int i=0; i<M; ++i) {
            int w, x, y, z;
            scanf("%d%d%d%d", &w, &x, &y, &z);
            if (w==2) z = -z;
            --x; --y;
            st.update(0,x,y+1,z);
        }
        pii p = st.query(0, 0, N);
        printf("%d\n", p.second - p.first);
    }
}

// WA
