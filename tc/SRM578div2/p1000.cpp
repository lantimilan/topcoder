#include <vector>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

const int MOD = 1e9+7;
int dp[305];

class WolfInZooDivTwo
{
public:

vector<int> getint(const vector<string> &vs)
{
	vector<int> ans;
	string s;
	for (int i = 0; i < vs.size(); ++i) s += vs[i];
	istringstream iss(s);
	int k;
	while (iss >> k) ans.push_back(k);
	return ans;
}

int count(int N, vector <string> L, vector <string> R)
{
	vector<int> left, right;
	left = getint(L); right = getint(R);
	memset(dp, 0, sizeof dp);
	dp[0] = 1;
	for (int j = 1; j <= N; ++j) {
		for (int k = 0; k < j; ++k) {
			bool good = true;
			for (int i = 0; i < left.size(); ++i) {
				int a, b;
				a = left[i]; b = right[i];
				if (k-1 < a && b < j-1) good = false;
			}
			if (good) dp[j] += dp[k];
			if (dp[j] >= MOD) dp[j] -= MOD;
		}
	}
	int mx = 0;
	for (int i = 0; i < left.size(); ++i) mx = max(left[i], mx);
	int ans = 0;
	for (int p = mx+1; p <= N; ++p) {
		ans += dp[p];
		if (ans >= MOD) ans -= MOD;
	}
	return ans;
}
};
