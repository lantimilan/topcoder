#include <algorithm>
#include <vector>
using namespace std;

class TeamContest
{
public:
int worstRank(vector <int> strength)
{
	vector<int> tmp(3);
	for (int i=0; i<3; ++i) tmp[i] = strength[i];
	sort(tmp.begin(), tmp.end());
	int target = tmp[0] + tmp[2];
	int n = strength.size();
	tmp.resize(n-3);
	for (int i=3; i<n; ++i) tmp[i-3] = strength[i];
	
	sort(tmp.begin(), tmp.end());
	int l, r;
	l = 0; r = tmp.size() - 1;
	int cnt = 1;
	while (l+1 < r) {  // need at least 3 elements
		if (tmp[l] + tmp[r] > target) {
			l += 2; r--; cnt++;
		} else {
			l++;
		}
	}
	return cnt;
}
};
