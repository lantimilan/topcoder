// =========================================================
// 
//       Filename:  travel.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/05/2012 11:31:28 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/05/2012, LI YAN
// 
// =========================================================

#include <cstring>
#include <iostream>
using namespace std;

typedef long long int64;

int edge[105][105];
int S[105];
int64 node[105];

int main()
{
    int N, M, K; cin >> N >> M >> K;
    memset(edge, -1, sizeof edge);
    for(int i=0; i<M; ++i) {
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        edge[a][b] = edge[b][a] = c;
    }
    for(int i=0; i<N; ++i) cin >> S[i];

    node[0] = K;
    bool update;
    while(true) {
        update=false;
        // Bellman-Ford shortest path with negative edge
        for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j) if (i!=j && edge[i][j]>=0) {
            if (node[i]>= edge[i][j]) {
                int64 val = (node[i]+S[j]-edge[i][j])/2;
                if (val > node[j]) { node[j]=val; update=true; }
            }
        }
        //cout << node[N-1] << endl;
        if (!update) break;
    }
    cout << node[N-1] << endl;
}

// Travel   cpp     2012-05-06 13:05:19     Processed   Accepted
// Score: 100
//  View Details
//
// the statement says that update is (node[i]+S[j])/2 if even and
// (node[i]+S[j]-1)/2 if odd
// but this does not agree with the example
//
// UPDATE:
// No, you need to pay the toll, which is edge[i][j]
// So the update is (node[i]+S[j]-edge[i][j])/2
