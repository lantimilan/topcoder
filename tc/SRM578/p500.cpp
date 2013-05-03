#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
using namespace std;

const int MOD = 1e9+7;
int dp[305][305];
bool contained[301][301];

class WolfInZooDivOne
{
public:
vector<int> getvec(const vector<string> &vec)
{
	string s;
	for (int i = 0; i < vec.size(); ++i) {
		s += vec[i];
	}
	istringstream iss(s);
	int k;
	vector<int> ans;
	while (iss >> k) ans.push_back(k);
	return ans;
}

int count(int N, vector <string> L, vector <string> R)
{
	vector<int> left, right;
	left = getvec(L); //cout << left[0] << ' ' << left[1] << endl;
	right = getvec(R);

	memset(contained, 0, sizeof contained);
	memset(dp, 0, sizeof dp);

	for (int i = 1; i <= N; ++i)
	for (int j = i+1; j <= N; ++j)
	{
		bool inside = false;
		for (int k = 0; k < left.size(); ++k) {
			if (left[k] <= i-1 && j-1 <= right[k]) {
				inside = true; break;
			}
		}
		contained[i][j] = inside;
	}

	for (int i = 0; i <= N; ++i) dp[0][i] = 1;  // 0 and 1 wolf
	// 2 or more wolves and last two at l and r
	for (int r = 1; r <= N; ++r)
	for (int l = 1; l < r; ++l)
	{
		dp[l][r] += dp[0][l];
		for (int p = 1; p < l; ++p) if (!contained[p][r]) {
			dp[l][r] += dp[p][l];
			if (dp[l][r] >= MOD) dp[l][r] -= MOD;
		}
	}
	int ans = 0;
	for (int r = 1; r <= N; ++r)
	for (int l = 0; l < r; ++l)
	{
		ans += dp[l][r];
		if (ans >= MOD) ans -= MOD;
	}
	return (ans+1)%MOD;
}
};

// PASS system test
// cannot finish during contest
