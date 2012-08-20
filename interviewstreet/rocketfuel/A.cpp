// =========================================================
// 
//       Filename:  A.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/19/2012 12:08:24 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  LI YAN (lyan), lyan@cs.ucr.edu
//        Company:  U of California Riverside
//      Copyright:  Copyright (c) 05/19/2012, LI YAN
// 
// =========================================================

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <utility>
using namespace std;

typedef pair<int,int> pii;
typedef pair<int, pair<pii,int> > mypair; // dist, (r,c), h

int N, M;
int graph[305][305];
int dist[305][305][12];
bool seen[305][305][12];

class MyCmp {
public:
    bool operator()(const mypair& p1, const mypair& p2) {
        return p1.first > p2.first;
    }
};
priority_queue<mypair, vector<mypair>, MyCmp> pq;

int main()
{
    scanf("%d%d", &N, &M);
    int pond[2], farm[2]; scanf("%d%d%d%d ", pond, pond+1, farm, farm+1);
    --pond[0]; --pond[1];
    --farm[0]; --farm[1];
    char line[305];
    for(int i=0; i<N; ++i) {
        scanf("%s", line);
        for(int j=0; j<M; ++j) {
            graph[i][j] = line[j]-'0';
        }
    }
    memset(dist, -1, sizeof dist);
    int cap = graph[pond[0]][pond[1]];
    int r0=pond[0], c0=pond[1];
    pq.push(mypair(0, make_pair(pii(r0,c0), cap)));
    while(!pq.empty()) {
        int dnow = pq.top().first;
        pii top = pq.top().second.first;
        int height = pq.top().second.second;
        pq.pop();
        int r=top.first, c=top.second;
        if (seen[r][c][height]) continue;
        seen[r][c][height]=true; dist[r][c][height]=dnow;

        int dir[][2]={{-1,0},{0,+1},{+1,0},{0,-1}};
        for(int x=0; x<4; ++x) {
            int r2=r+dir[x][0];
            int c2=c+dir[x][1];
            if (0<=r2 && r2<N && 0<=c2 && c2<M) {
                int hnext = graph[r2][c2];
                for(int h=0; h<=height; ++h) {
                    int cost = abs(h-hnext);
                    if (!seen[r2][c2][h]) {
                        int dnew = dnow+cost;
                        pq.push(mypair(dnew, make_pair(pii(r2,c2), h)));
                    }
                }
            }
        }
    }
    int ans=-1;
    for(int h=0; h<10; ++h) {
        int cost = dist[farm[0]][farm[1]][h];
        if (cost >=0) {
            if (ans<0 || ans > cost) ans=cost;
        }
    }
    printf("%d\n", ans);
}
