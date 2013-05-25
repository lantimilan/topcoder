#include <vector>
using namespace std;

class EelAndRabbit
{
public:
int getmax(vector <int> l, vector <int> t)
{
	vector<int> pos;
	for (int i = 0; i < l.size(); ++i) {
		pos.push_back(t[i]);
		pos.push_back(t[i] + l[i]);
	}
	int best = 0;
	for (int i = 0; i < pos.size(); ++i)
	for (int j = i+1; j < pos.size(); ++j)
	{
		int curr = 0;
		int p1 = pos[i], p2 = pos[j];
		for (int k = 0; k < l.size(); ++k) {
			if (t[k] <= p1 && p1 <= t[k]+l[k]) curr++;
			else if (t[k] <= p2 && p2 <= t[k]+l[k]) curr++;
		}
		best = max(best, curr);
	}
	return best;
}
};
