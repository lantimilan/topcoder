#include <algorithm>
#include <vector>
using namespace std;

class TeamContestEasy
{
public:
int worstRank(vector <int> strength)
{
	int a[3];
	a[0] = strength[0];
	a[1] = strength[1];
	a[2] = strength[2];
	sort(a, a+3);
	int rank = 1;
	int score = a[1] + a[2];
	int n = strength.size();
	vector<int> used(n, 0);
	sort(strength.begin()+3, strength.end());
	for (int i = n-1; i >=3; --i) if (!used[i]) {
		bool found = false;
		for (int j = 3; j < i; ++j) if (!used[j]) {
			if (strength[i] + strength[j] > score) {
				for (int k = 3; k < j; ++k) if (!used[k]) {
					found = true;
					used[i] = used[j] = used[k] = 1;
					rank++;
					goto done;
				}
			}
		}
		done:
		if (!found) break;
	}
	return rank;
}
};
