// prob280C.cpp
//
// consider a single item a[i]
// a[i] only contribute 1 to total cost if a[i]
// is selected before any node in path a[i] to root
// this happens with probability 1.0 / depth[i]
//
// work on a simpler problem which the nodes form
// a list instead of a tree also helps

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

vector<int> vec[100000+5];
int seen[100000+5];

double dfs(int root, int depth)
{
    seen[root] = 1;
    double ans = 0.0;
    ans += 1.0 / (depth + 1);
    for (int x = 0; x < vec[root].size(); ++x) {
        int next = vec[root][x];
        if (seen[next]) continue;
        ans += dfs(next, depth+1);
    }
    return ans;
}

int main()
{
    int n; cin >> n;
    for (int i=0; i<n-1; ++i) {
        int a, b; cin >> a >> b; --a; --b;
        vec[a].push_back(b);
        vec[b].push_back(a);
    }
    double cost = dfs(0, 0);
    cout << fixed << setprecision(9) << cost << endl;
}

// Accepted
