// prob520B.cpp
#include <iostream>
#include <map>
#include <queue>
using namespace std;

map<int, int> dist;

int main()
{
    int n, m; cin >> n >> m;
    dist[n] = 0;
    queue<int> que; que.push(n);
    while (!que.empty()) {
        int head = que.front(); que.pop();
        if (head == m) {
            break;
        }
        int next = head - 1;
        if (next > 0 && !dist.count(next)) {
            que.push(next);
            dist[next] = dist[head] + 1;
        }
        next = head * 2;
        if (next <= 2 * m && !dist.count(next)) {
            que.push(next);
            dist[next] = dist[head] + 1;
        }
    }
    cout << dist[m] << endl;
}
