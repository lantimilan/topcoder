#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

class MarblePositioning
{
public:

int fact(int n)
{
	int t = 1;
	for (int i = 2; i <= n; ++i) t *= i;
	return t;
}

double totalWidth(vector <int> radius)
{
	double ans = 1e9 * 100;  // if all size equal to 1e9, then the separation is 7*1e9*2 = 14 * 1e9
	int n = radius.size();
	vector<int> vec(n);
	for (int i = 0; i < n; ++i) vec[i] = i;
	int cnt = 0;
	do {
		++cnt;
		double p[10];
		for (int i = 0; i < n; ++i) p[i] = 0.0;

		for (int i = 1; i < n; ++i) {
		double curr = 0;
		for (int j = i-1; j >= 0; --j) {
			double r1 = radius[vec[j]];
			double r2 = radius[vec[i]];
			double sum = r1 + r2;
			double sub = r1 - r2;
			double shift = sqrt(sum*sum - sub*sub);
			curr = max(curr, p[j] + shift);
		}
		p[i] = curr;
		}
		ans = min(ans, p[n-1]);
	} while (next_permutation(vec.begin(), vec.end()));
    // here is the catch, to ask next_permutation iterate all perms
    // you need to sort the array first
	assert(cnt == fact(n));
	return ans;
}
};
