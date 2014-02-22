#include <vector>
#include <string>
using namespace std;

class FoxAndWord
{
public:

bool isInteresting(string s1, string s2)
{
	if (s1.length() != s2.length()) return false;
	for (int l = 1; l < s1.size(); ++l) {
		string tmp = s1.substr(l) + s1.substr(0, l);
		if (tmp == s2) return true;
	}
	return false;
}

int howManyPairs(vector <string> words)
{
	int ans = 0;
	for (int i = 0; i < words.size(); ++i)
	for (int j = i+1; j < words.size(); ++j)
		if (isInteresting(words[i], words[j]))
			ans++;
	
	return ans;
}
};
