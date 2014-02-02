#include <algorithm>
#include <string>
using namespace std;

class EllysSubstringSorter
{
public:

string reorder(string s, int start, int len)
{
	sort(s.begin()+start, s.begin()+start+len);
	return s;
}

string getMin(string S, int L)
{
	string best = S;
	for (int i = 0; i <= S.length() - L; ++i) {
		string cur = reorder(S, i, L);
		best = min(best, cur);
	}
	return best;
}

};
