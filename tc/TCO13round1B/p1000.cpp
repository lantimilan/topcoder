#include <vector>
#include <string>
#include <cassert>
#include <iostream>
using namespace std;

// match two words by matching substr of length 2
class EllysReversals
{
public:
bool match(string a, string b)
{
	int n = a.size();
	if (n != b.size()) return false;
	for (int i = 0; i < n; i+=2) {
		string sub = a.substr(i, 2);
		int j;
		for (j = 0; j < n; j += 2) {
			if (b[j] == sub[0] && b[j+1] == sub[1]) break;
			if (b[j] == sub[1] && b[j+1] == sub[0]) break;
		}
		if (j < n) b[j] = b[j+1] = '*';
	}
	for (int j = 0; j < n; ++j) if (b[j] != '*') return false;
	return true;
}

int getMin(vector <string> words)
{
	for (;;) {
		bool update = false;
		for (int i = 0; i < words.size(); ++i) if (words[i] != "") {
			for (int j = 0; j < words.size(); ++j) if (i != j) {
				if (match(words[i], words[j])) {
					update = true;
					words[i] = words[j] = "";
				}
			}
		}
		if (!update) break;
	}
	int cnt = 0;
	for (int i = 0; i < words.size(); ++i) if (words[i] != "") { cnt++; }
	return cnt;
}
};
