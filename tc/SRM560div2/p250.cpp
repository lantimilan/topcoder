#include <cstdlib>
#include <string>
using namespace std;

class TypingDistance
{
public:
int minDistance(string keyboard, string word)
{
	int pos;
	for (pos=0; pos < keyboard.size(); ++pos)
		if (keyboard[pos] == word[0]) break;
	int ans = 0;
	for (int i=1, prev=pos; i<word.size(); ++i) {
		for (; keyboard[pos] != word[i]; pos = (pos+1) % keyboard.size())
			;
		ans += abs(pos - prev);
		prev = pos;
	}
	return ans;
}
};

// wrap around