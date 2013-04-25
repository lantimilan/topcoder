#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define sz(a) int(a.size())

int vis[60][60];

class ArcadeManao
{ 
public: 
    void dfs(int L, int r, int c, const vector<string> &graph) {
        vis[r][c] = 1;
        // use ladder
        for (int row = r - L; row <= r+L; ++row)
        if (1 <= row && row <= graph.size()) {
            if (!vis[row][c] && graph[row-1][c-1] == 'X') dfs(L, row, c, graph);
        }
        // walk horizontally
        for (int col = c-1; col >= 1 && graph[r-1][col-1] == 'X'; --col) {
            if (!vis[r][col] && graph[r-1][col-1] == 'X') dfs(L, r, col, graph);
        }
        for (int col = c+1; col <= graph[0].size() && graph[r-1][col-1] == 'X'; ++col) {
            if (!vis[r][col] && graph[r-1][col-1] == 'X') dfs(L, r, col, graph);
        }
    }

    bool getcoin(int L, int crow, int ccol, const vector<string> &graph) {
        memset(vis, 0, sizeof vis);
        int r=graph.size(), c=1;
        dfs(L, r, c, graph);
        return vis[crow][ccol];
    }
    int shortestLadder(vector <string> level, int coinRow, int coinColumn) 
    { 
        int N = level.size();
        int lo = -1, hi = N;  // lo is infeasible and hi is feasible
        while (lo + 1 < hi) {
            int L = (lo + hi) / 2;
            if (getcoin(L, coinRow, coinColumn, level)) {
                hi = L;
            } else {
                lo = L;
            }
        }
        return hi;
    } 
    
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
