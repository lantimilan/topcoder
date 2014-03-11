#include <vector>
#include <algorithm>
using namespace std;

class SplitIntoPairs
{
public:

// 1. pair + and - separately
// 2. use min in each set if not exhausted in step 1
int makepairs(vector <int> A, int X)
{
	vector<int> plus, minus;
	for (int i = 0; i < A.size(); ++i) {
		if (A[i] >= 0) plus.push_back(A[i]);
		else minus.push_back(A[i]);
	}
	sort(plus.begin(), plus.end());
	sort(minus.begin(), minus.end());
	int ans = A.size() / 2;
	if (plus.size() & 1) {
		int a = plus[0];
		int b = minus[minus.size() - 1];
		if ((long long)a * b >= X) {}
		else ans--;
	}
	return ans;
}
};
