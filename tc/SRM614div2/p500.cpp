#include <vector>
using namespace std;

// only two choices for xmin, x1 and x1-1
// only two choices for xmax, and ymin, ymax
// first get rectangle, then expand to square
class MinimumSquareEasy
{
public:
long long minArea(vector <int> x, vector <int> y)
{
	long long ans = 1LL << 50;
	for (int i = 0; i < x.size(); ++i) {
		for (int j = i+1; j < x.size(); ++j) {
			vector<int> xx, yy;
			for (int t = 0; t < x.size(); ++t) 
				if (t != i && t != j) {
					xx.push_back(x[t]);
					yy.push_back(y[t]);
				}
			long long cur = solve(xx, yy);
			ans = min(ans, cur);
		}
	}
	return ans * ans;
}

long long solve(vector<int> x, vector<int> y)
{
	long long ans = 1LL << 50;
	int x1, x2, y1, y2;
	x1 = x[0];
	for (int i = 1; i < x.size(); ++i) {
		if (x[i] < x1) x1 = x[i];
	}
	x2 = x[0];
	for (int i = 1; i < x.size(); ++i) {
		if (x[i] > x2) x2 = x[i];
	}
	y1 = y[0];
	for (int i = 1; i < y.size(); ++i) {
		if (y[i] < y1) y1 = y[i];
	}
	y2 = y[0];
	for (int i = 1; i < y.size(); ++i) {
		if (y[i] > y2) y2 = y[i];
	}
	for (int d1 = 0; d1 >= -1; d1--)
	for (int d2 = 0; d2 <= 1; d2++)
	for (int d3 = 0; d3 >= -1; d3--)
	for (int d4 = 0; d4 <= 1; d4++)
	{
		int xx1 = x1 + d1;
		int xx2 = x2 + d2;
		int yy1 = y1 + d3;
		int yy2 = y2 + d4;
		long long s = max(xx2 - xx1, yy2 - yy1);

		// xx1, xx1+s, yy1, yy1+s
		if (check(xx1, xx1+s, yy1, yy1+s, x, y)) ans = min(ans, s);
		// xx2-s, xx2, yy1, yy1+s
		if (check(xx2-s, xx2, yy1, yy1+s, x, y)) ans = min(ans, s);
		// xx1, xx1+s, yy2-s, yy2
		if (check(xx1, xx1+s, yy2-s, yy2, x, y)) ans = min(ans, s);		
		// xx2-s, xx2, yy2-s, yy2
		if (check(xx2-s, xx2, yy2-s, yy2, x, y)) ans = min(ans, s);
	}
	return ans;
}

bool check(int x1, int x2, int y1, int y2, const vector<int> &x, const vector<int> &y)
{
	for (int i = 0; i < x.size(); ++i) {
		if (x1 < x[i] && x[i] < x2 && y1 < y[i] && y[i] < y2) {}
		else return false;
	}
	return true;
}
};
