#include <string>
#include <iostream>
using namespace std;

class Stamp {
public:

int get_id(char ch)
{
	if (ch == 'R') return 0;
	if (ch == 'G') return 1;
	if (ch == 'B') return 2;
	return -1;
}

bool check(int s[], int l, int r, int c)
{
	for(int i=l; i<r; ++i) {
		if (s[i]>=0 && s[i] != c) return false;
	}
	return true;
}

void update(int &a, int b)
{
	if (b>=0) {
		if (a<0) a = b;
		else if (a>b) a = b;
	}
}

int getMinimumCost(string desiredColor, int stampCost, int pushCost)
{
	int n = desiredColor.size();
	int dp[60][3], goal[60];
	for(int i=0; i<n; ++i)
		goal[i] = get_id(desiredColor[i]);

	int ans=-1;		
	for(int s=1; s<=n; ++s) 	
	{
		int unit = pushCost;
		memset(dp, -1, sizeof dp);
		for(int c=0; c<3; ++c)
		{
			if (check(goal, 0, s, c))
				dp[s][c] = unit;
		}
		for(int i=s+1; i<=n; ++i) 
		for(int c=0; c<3; ++c)
		if (check(goal, i-s, i, c))
		{
			int curr = -1;
			for(int c2=0; c2<3; ++c2)
				if (dp[i-s][c2]>=0) {
					update(curr, dp[i-s][c2] + unit);
				}
			for(int j=i-s+1; j<i; ++j)
				if (dp[j][c]>=0)
					update(curr, dp[j][c] + unit);
			dp[i][c] = curr;
		}		
		for(int c=0; c<3; ++c) {
		//cout << s << ' ' << n << ' ' << c << ' ' << dp[n][c] << endl;		
		if (dp[n][c]>=0) update(ans, dp[n][c] + s*stampCost);
		}
	}
	return ans;
}
};
