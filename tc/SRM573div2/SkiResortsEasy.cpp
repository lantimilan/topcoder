#include <vector>
using namespace std;

class SkiResortsEasy
{
public:
int minCost(vector <int> altitude)
{
	int ans = 0;
	for (int i = 1; i < altitude.size(); ++i) {
		int d = altitude[i] - altitude[i-1];
		if (d > 0) {
			ans += d;
			altitude[i] = altitude[i-1];
		}
	}
	return ans;
}
};
