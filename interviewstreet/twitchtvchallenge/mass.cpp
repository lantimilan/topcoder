// =========================================================
// 
//       Filename:  mass.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/05/2012 03:55:48 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/05/2012, LI YAN
// 
// =========================================================

#include <cassert>
#include <cstdio>
using namespace std;

bool edge[105][105];
bool path[105][105];
int W[105];
int K;

// transitive closure
void closure()
{
    for(int i=0; i<K; ++i) path[i][i]=true;
    for(int i=0; i<K; ++i)
    for(int j=0; j<K; ++j) if (i!=j)
        path[i][j] = edge[i][j];

    for(int k=0; k<K; ++k)
    for(int i=0; i<K; ++i)
    for(int j=0; j<K; ++j)
        if (path[i][k] && path[k][j]) path[i][j]=true;
}

void solve()
{
    closure();
    int n = K;
    int used[105]={0};
    int taken[105]={0};
    int conf[105];
    while(n--) {
        int x=-1, pos=-1;
        for(int i=0; i<K; ++i) if (!used[i]) {
            if (x<0 || W[i] > W[x]) x=i;
        }
        assert(x>=0);
        used[x]=1;
        for(int j=0; j<K; ++j) if (path[x][j] && !taken[j]) {
            pos=j;
        }
        assert(pos>=0);
        conf[pos]=x; taken[pos]=1;
    }
    for(int i=0; i<K; ++i) { 
        if (i) putchar(' ');
        printf("%d", W[conf[i]]);
    }
    putchar('\n');
}

int main()
{
    scanf("%d", &K);
    for(int i=0; i<K; ++i) scanf("%d", &W[i]);
    for(int i=0; i<K; ++i) {
        char line[105];
        scanf("%s", line);
        for(int j=0; j<K; ++j) {
            edge[i][j] = (line[j]=='Y')?true:false;
        }
    }
    solve();
}

// Centre of Mass   cpp     2012-05-06 04:44:56     Processed   Accepted
// Score: 100
//  View Details
