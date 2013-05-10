#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;


// everyone in same row is not in her room
// everyone else contributes rating / R
class EllysRoomAssignmentsDiv1
{
public:

vector<int> get_vec(vector<string> vs)
{
	vector<int> vec;
	string s;
	for (int i = 0; i < vs.size(); ++i) s += vs[i];
	istringstream iss(s);
	int k;
	while (iss >> k) vec.push_back(k);
	return vec;
}

double getAverage(vector <string> ratings)
{
	vector<int> regs = get_vec(ratings);
	int N = regs.size();
	int R = (N + 19) / 20;
	int elly = regs[0];

	sort(regs.begin(), regs.end(), greater<int>());
	int index = -1;
	for (int g = 0; g < N / R; ++g) {
		for (int i = 0; i < R; ++i)
			if (regs[g * R + i] == elly) { index = g; break; }
	}
	double ans = 0.0;
	int cnt;
	double sum = 0;
	for (int g = 0; g < N / R; ++g) if (g != index) {
		for (int i = 0; i < R; ++i) sum += 1.0 * regs[g*R+i] / R;
	}
	sum += elly;
	if (index < 0) {  // last incomplete group
		cnt = (N + R-1) / R;
		ans = sum / cnt;
	} else {
		int rem = N % R;
		for (int i = N-1; i >= N-rem; --i) {
			cnt = (N + R-1) / R;
			ans += 1.0 / R * (sum + regs[i]) / cnt;
		}
		ans += (1 - 1.0*rem/R) * sum / (N / R);
	}
	return ans;
}
};
