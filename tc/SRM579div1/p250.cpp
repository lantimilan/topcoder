#include <vector>
#include <string>
using namespace std;

class UndoHistory
{
public:
// important: double click restore can be used no more than once
//
vector<string> vec;

bool is_prefix(string pre, string text)
{
	if (pre.length() > text.length()) return false;
	for (int i = 0; i < pre.length(); ++i)
		if (pre[i] != text[i]) return false;
	return true;
}

int get_pre(string text)
{
	int len = 0;
	for (int i = 0; i < vec.size(); ++i) if (is_prefix(vec[i], text)) {
		len = max(len, (int)vec[i].length());
	}
	return len;
}

int minPresses(vector <string> lines)
{
	vec.push_back("");
	int ans = 0;
	for (int i = 0; i < lines.size(); ++i) {
		string buf = i > 0 ? lines[i-1] : "";
		string curr = lines[i];
		// use either buf or vec[] to start current line
		// then type the rest
		int k = 0;
		int len = get_pre(curr);
		if (is_prefix(buf, curr) && buf.length() + 2 >= len) {
			k += buf.length();  // use buffer
		} else {
			k += len; ans += 2;  // use vec
		}
		ans += curr.length() - k + 1;  // +1 for ENTER
		// fill history
		for (; k < curr.length(); ++k) {
			vec.push_back(curr.substr(0, k+1));
		}

	}
	return ans;
}
};
