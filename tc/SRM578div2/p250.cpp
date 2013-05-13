#include <vector>
using namespace std;

class DeerInZooDivTwo
{
public:

vector <int> getminmax(int N, int K)
{
	int x = N - (K+1) / 2;
	int y = max(0, N-K);
	vector<int> ans;
	ans.push_back(y);
	ans.push_back(x);
	return ans;
}

};
