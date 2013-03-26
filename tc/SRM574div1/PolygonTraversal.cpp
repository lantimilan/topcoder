// this is like TSP problem, so think about O(2^n * n) algorithm
// given a prefix with last, we want to extend the prefix by node = next
// In this problem we need to know whether prefix intersects (last, next)
// so it appears we need to know the actual prefix, not only the mask of all
// nodes in prefix, but then the algorithm would be n factorial which is too slow!
//
// Now comes the observation: we only need to know the subset of nodes in prefix,
// to determine intersection, their order does not matter. Let S be the set of nodes
// in prefix, then S contains a pair (a, b) that intersects (last, next) if and only
// if S contains nodes both inside and outside the range of (a, b), regardless of
// how nodes in S are ordered. Because we only need to know whether S crosses
// (last, next) or not, this check is enough.

#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;


long long dp[1<<18][20];  // careful, dp[1<<20][20] for long long will mem limit exceeded, SIGKILL

class PolygonTraversal
{
public:

bool inrange(int a, int b, int val)
{
	assert(a < b && a != val && b != val);
	return a < val && val < b;
}

bool cross(int a, int b, const vector<int> &vec)
{
	bool inside, outside;
	inside = outside = false;
	for (int i = 0; i < vec.size(); ++i) {
		int k = vec[i];
		if (inrange(a, b, k)) inside = true;
		else outside = true;
	}
	return inside && outside;
}

long long count(int N, vector <int> points)
{	
	for (int i = 0; i < points.size(); ++i) points[i]--;
	int start = 0;
	for (int i = 0; i < points.size(); ++i) start |= 1 << points[i];
	dp[start][points.back()] = 1;
		
	for (int mask = 0; mask < (1 << N); ++mask) if ((mask & start) == start) {  // mask contains start
		for (int last = 0; last < N; ++last) if (mask & 1 << last) {  // mask has last
			vector<int> prefix;
			for (int i = 0; i < N; ++i) if ((mask & 1 << i) && i != last)
				prefix.push_back(i);
			for (int next = 0; next < N; ++next) if (!(mask & 1 << next)) {  // next is not in mask
				int a, b;
				a = min(last, next); b = max(last, next);
				if (cross(a, b, prefix)) {
					dp[mask | 1<<next][next] += dp[mask][last];
				}
			}
		}
	}
	long long ans = 0;
	for (int last = 0; last < N; ++last) if (last != points[0]) {
		vector<int> vec;
		for (int i = 0; i < N; ++i) if (i != points[0] && i != last) vec.push_back(i);
		int a, b;
		a = min(points[0], last); b = max(points[0], last);
		if (cross(a, b, vec))
			ans += dp[(1<<N) - 1][last];
	}
	return ans;
}  // end of method

};  // end of class
