#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class UndoHistory
{
public:

bool is_prefix(string s1, string s2)
{
	if (s1.length() > s2.length()) return false;
	for (int i = 0; i < s1.length(); ++i)
		if (s1[i] != s2[i]) return false;
	return true;
}

int minPresses(vector <string> lines)
{
	vector<string> history;
	history.push_back("");
	int ans = 0;
	string buf = "";
	for (int i = 0; i < lines.size(); ++i) {
		string curr = lines[i];
		int pos = -1, cost = 0;
		if (is_prefix(buf, curr)) {
			pos = buf.length();
			cost = 0;
		}
		int pre = 0;
		for (int j = 0; j < history.size(); ++j) {
			string s = history[j];
			if (is_prefix(s, curr)) pre = max(pre, (int)s.length());
		}
		if (pos < 0 || pos+2 < pre) { pos = pre; cost = 2; }
		ans += cost + curr.length() - pos;
		for (int p = pos+1; p <= curr.length(); ++p)  // add all length >= pos substr to history
			history.push_back(curr.substr(0, p));
		buf = curr;
	}
	return ans + lines.size();
}
};
