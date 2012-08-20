// https://twitchtvchallenge.interviewstreet.com/challenges/dashboard/#problems
// =========================================================
// 
//       Filename:  arrangement.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  05/05/2012 04:25:18 PM
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
#include <cstring>
using namespace std;

int N;
bool graph[1005][1005];
int deg[1005];
int pred[1005];
bool vis[1005];
int ans[1005];
int cnt;

int dfs(int s)
{
    if (cnt >= N) return s;
    vis[s]=true; cnt++;
    for(int x=0; x<N; ++x) if (!vis[x] && graph[s][x]) {
        int res = dfs(x);
        if (res>=0) { pred[x]=s; return res; }
    }
    vis[s]=false; cnt--;
    return -1;
}

void solve()
{
    memset(graph, 0, sizeof graph);
    scanf("%d", &N);
    char line[1005];
    for(int i=0; i<N; ++i) {
        scanf("%s", line);
        for(int j=0; j<N; ++j) {
            graph[i][j] = (line[j]-'0');
        }
    }
    bool found=false;
    for(int s=0; s<N; ++s) {
        memset(vis, 0, sizeof vis);
        cnt=1;
        int last = dfs(s);
        if (last >=0) {
            assert(cnt==N);
            found=true;
            int x=last;
            for(--cnt; cnt>=0; --cnt) {
                ans[cnt] = x; x = pred[x];
            }
            break;
        }
    }
    if (found) { printf("Yes");
        for(int i=0; i<N; ++i) printf(" %d", ans[i]);
        putchar('\n');
    }
    else puts("No");
}

int main()
{
    int T; scanf("%d", &T);
    for(int t=0; t<T; ++t) solve();
}

// Arrangement  cpp     2012-05-06 10:11:00     Processed   
// Score: 100
//  View Details
