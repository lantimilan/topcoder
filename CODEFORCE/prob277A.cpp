// prob277A.cpp
//
// count number of components
// ans is comp - 1

#include <iostream>
using namespace std;

int adj[105][105];
int lang[105][105]; // lang[i][j] means person[i] knows language[j]
int vis[105];
int n, m;

void dfs(int s)
{
    vis[s] = 1;
    for (int i = 0; i < n; ++i) if (!vis[i] && adj[s][i]) {
        dfs(i);
    }
}

int main()
{
    cin >> n >> m;
    bool good = false;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int l; cin >> l;
            lang[i][l] = 1;
            good = true;
        }
    }
    for (int l = 1; l <= m; ++l)
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j)
            if (lang[i][l] && lang[j][l]) adj[i][j] = adj[j][i] = 1;
    }
    int comp = 0;
    for (int i = 0; i < n; ++i) if (!vis[i]) {
        dfs(i); comp++;
    }
    if (good) comp--;
    cout << comp << endl;
}

// Accepted
// the tricky case is when all k[i] is zero
