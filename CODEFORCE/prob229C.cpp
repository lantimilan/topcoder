// =========================================================
// 
//       Filename:  prob229C.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/02/2012 09:46:25 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 10/02/2012, LI YAN
// 
// =========================================================


// given a complete graph
// edges are partitioned into set A and B
// count number of triangles formed by all A edges
// and those formed by all B edges
//
// algorithm:
// for each pair of edges with a common endpoint, if both are A edges
// or both are B edges, then weight(v) add 2,
// if one of edge is A edge and the other is B edge, then weight(v) add -1
//
// then for each A triangle or B triangle, they contribute to the sum +6
// for each non-valid triangle, they contribute to the sum 0
//
// calculate the sum by summing over all vertices, for each vertex check (d
// choose 2) edges
// 
// stunning idea!

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

vector<vector<int> > adj;

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    if (n<=2) {
        cout << 0 << endl;
        return 0;
    }
    adj.resize(n);
    for(int i=0; i<m; ++i) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int64 sum=0;
    for(int i=0; i<n; ++i) {
        int64 d = adj[i].size();
        if (d==0) sum += (int64)(n-1)*(n-2);
        else {
            sum += d*(d-1);
            if (n-2-d>=0)
                sum += (n-1-d)*(n-2-d);
            sum -= d*(n-1-d);
        }
    }
    assert(sum % 6 == 0);
    cout << sum/6 << endl;
}

// Accepted
// it is not necessary to store adj[][]
