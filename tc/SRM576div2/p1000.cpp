#include <string>
#include <vector>
using namespace std;

// try each length l=1 to W
// pos = (i,j) = (a+i0, b+j0) % l
// each pos is either consistent or untouched (26 choices)

class CharacterBoard2
{
public:

int countGenerators(vector <string> fragment, int W, int i0, int j0)
{
	const int MOD = (int)1e9 + 9;
	int ans = 0;
	for (int l = 1; l <= W; ++l) {
		bool good = true;
		string word(l, '?');
		for (int a = 0; a < fragment.size(); ++a)
		for (int b = 0; b < fragment[a].size(); ++b)
		{
			char ch = fragment[a][b];
			int i = a + i0;
			int j = b + j0;
			int pos = (i * W + j) % l;
			if (word[pos] == '?') word[pos] = ch;
			else if (word[pos] != ch) { good = false; goto done; }
		}
		done:
		if (!good) continue;
		int empty = 1;
		for (int i = 0; i < l; ++i) if (word[i] == '?') {
			empty = (long long)empty * 26 % MOD;
		}
		ans += empty;
		if (ans >= MOD) ans -= MOD;
	} 
	return ans;
}
};
