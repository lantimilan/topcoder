// consider the k points in an opt square
// they form a rectangle with boundary x1, x2, y1, y2
// so we can use all pairs of x[i], x[j] as x1, x2
// then sort by y for all points with x[i] < xval < x[j]
// then a possible square is x1, x2, y[p], y[p+K-1]

#include <algorithm>
#include <vector>
using namespace std;

class MinimumSquare
{
public:

long long minArea(vector <int> x, vector <int> y, int K)
{
	int ans = -1;
	int N = x.size();
	for (int i = 0; i < N; ++i)
	for (int j = i; j < N; ++j)
	{
		int x1 = min(x[i], x[j]);
		int x2 = max(x[i], x[j]);
		vector<int> yvals;
		for (int l = 0; l < N; ++l) {
			if (x1 <= x[l] && x[l] <= x2) yvals.push_back(y[l]);
		}
		sort(yvals.begin(), yvals.end());
		for (int l = 0; l + K <= yvals.size(); ++l) {
			int dx = x2 - x1;
			int dy = yvals[l + K -1] - yvals[l];
			int cur = max(dx, dy) + 2;
			update(ans, cur);
		}
	}
	
	return (long long)ans * ans;
}

template<class T>
void update(T &a, T b)
{
	if (a < 0 || a > b) a = b;
}

};
