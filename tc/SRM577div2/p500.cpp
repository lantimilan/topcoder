#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <algorithm>
using namespace std;

class EllysRoomAssignmentsDiv2
{
public:

vector<int> get_vec(vector<string> vs)
{
	string s;
	for (int i = 0; i < vs.size(); ++i) s += vs[i];
	istringstream iss(s);
	int k;
	vector<int> vec;
	while (iss >> k) vec.push_back(k);
	return vec;
}

double getProbability(vector <string> ratings)
{
	vector<int> regs = get_vec(ratings);
	int elly = regs[0];
	sort(regs.begin(), regs.end(), greater<int>());
	int N = regs.size();
	int R = (N + 19) / 20;
	if (elly == regs[0]) return 1.0;
	for (int i = 0; i < R; ++i) if (elly == regs[i]) return 0.0;
	
	return 1.0 / R;
}

};
