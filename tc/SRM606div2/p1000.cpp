#include <cassert>
#include <string>
#include <map>
#include <vector>
#include <iostream>
using namespace std;

// each box can be at 1, 2 or 4 (at most double twice with two neighbors)
// so conf for each box is 0, 1, 2, or 4, total 4^10 states, or 2^20 states

map<vector<int>, int> dp;

class EllysCandyGame
{
public:

bool is_zero(const vector<int> &vec)
{
	for (int i = 0; i < vec.size(); ++i)
		if (vec[i] != 0) return false;
	return true;
}

int calc(vector<int> &vec, const vector<int> &src)
{
	if (is_zero(vec)) return 0;
	if (dp.count(vec)) return dp[vec];
	int best = -1000 * 100;
	for (int i = 0; i < vec.size(); ++i) if (vec[i]) {
		assert(vec[i] == 1 || vec[i] == 2 || vec[i] == 4);
		int cur = src[i] * vec[i];
		int old = vec[i];
		vec[i] = 0;
		if (0 <= i-1) vec[i-1] *= 2;
		if (i+1 < vec.size()) vec[i+1] *= 2;
		int diff = calc(vec, src);
		best = max(best, cur - diff);
		vec[i] = old;
		if (0 <= i-1) vec[i-1] /= 2;
		if (i+1 < vec.size()) vec[i+1] /= 2;
	}
	
	//cout << best << ": ";
	//for (int i = 0; i < vec.size(); ++i) cout << vec[i] << ' ';
	//cout << endl;
	return best;
}

string getWinner(vector <int> sweets)
{
	vector<int> vec(sweets.size(), 1);
	for (int i = 0; i < sweets.size(); ++i) if (sweets[i] == 0) vec[i] = 0;
	int diff = calc(vec, sweets);
	if (diff == 0) return "Draw";
	else if (diff > 0) return "Elly";
	else return "Kris";
}
};
