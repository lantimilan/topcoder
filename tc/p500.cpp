#include <vector>
#include <string>
#include <iostream>
using namespace std;

class ShoutterDiv1
{
public:

void dfs(int s, vector<int> &vis, const vector< vector<int> > &adj)
{
	//cout << "dfs " << s << endl;
	vis[s] = 1;
	int n = vis.size();
	for (int i = 0; i < n; ++i) if (!vis[i] && adj[s][i])
		dfs(i, vis, adj);
}

int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1,
	 		vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
{
	int n = 0;
	vector<int> enter, leave;
	for (int i = 0; i < s1.size(); ++i)
	for (int j = 0; j < s1[i].size(); ++j) {
		int ss = 0, tt = 0;
		ss = (s1000[i][j]-'0') * 1000 + (s100[i][j] - '0') * 100 + (s10[i][j] - '0') * 10 + s1[i][j] - '0';
		tt = (t1000[i][j]-'0') * 1000 + (t100[i][j] - '0') * 100 + (t10[i][j] - '0') * 10 + t1[i][j] - '0';
		enter.push_back(ss); leave.push_back(tt);
		++n;
		//cout << ss << ' ' << tt << endl;
	}
	vector< vector<int> > adj(n, vector<int>(n, 0));
	int edge = 0;
	for (int i = 0; i < n; ++i)
	for (int j = i+1; j < n; ++j) {
		if (leave[i] < enter[j] || leave[j] < enter[i]) {}
		else { adj[i][j] = adj[j][i] = 1; edge++; }
	}
	// check connected
	vector<int> vis(n, 0);
	dfs(0, vis, adj);
	for (int i = 0; i < n; ++i) if (!vis[i]) return -1;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int child = 0;
		for (int j = 0; j < n; ++j) if (i != j && adj[i][j]) child++;
		ans += n-1 - child;
	}
	return ans;
}
};
