#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// unbounded if two cycles share node

int root;
int cnt;
bool vis[60];

class BigOEasy
{
public:

void dfs(int start, const vector<string> &graph)
{
//cout << start << endl;
	vis[start] = true;
	for (int i = 0; i < graph[start].size(); ++i) if (graph[start][i] == 'Y') {
		int next = i;
		if (next == root) cnt++;
		if (!vis[next]) dfs(next, graph);
	}
}

string isBounded(vector <string> graph)
{
	int n = graph.size();
	for (int i = 0; i < n; ++i) {
		root = i;
		cnt = 0;
		memset(vis, 0, sizeof vis);
		dfs(i, graph);
		if (cnt > 1) return "Unbounded";
	}
	return "Bounded";
}
};
