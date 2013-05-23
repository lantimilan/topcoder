#include <string>
#include <cassert>
#include <algorithm>
using namespace std;

class TheNumberGameDiv2
{
public:

int subpos(const string &s1, const string &s2, int start)
{
	for (int p = start; p < s2.length(); ++p) {
		int p1 = 0;
		int p2 = p;
		for (; p1 < s1.length() && p2 < s2.length(); ++p1, ++p2)
			if (s1[p1] != s2[p2]) break;
		if (p1 >= s1.length()) return p;
	}
	return -1;
}

string int2str(int k)
{
	string s;
	do { s += k % 10; k /= 10; } while (k > 0);
	for (int i = 0, j = s.length()-1; i < j; ++i, --j) {
		char ch = s[i]; s[i] = s[j]; s[j] = ch;
	}
	return s;
}

int minimumMoves(int A, int B)
{
	string sa, sb;
	sa = int2str(A); sb = int2str(B);
	int best = 10000;
	int diff = sa.length() - sb.length(); // assert(diff >= 0);
	if (diff < 0) return -1;
	
	int pos = subpos(sb, sa, 0);
	if (pos == 0) best = diff;  // sb prefix of sa
	else if (pos > 0) best = diff + 2;  // sb substr of sa, nonempty pre to remove

	reverse(sb.begin(), sb.end());
	if (subpos(sb, sa, 0) >= 0) best = min(best, diff + 1);  // sb_reverse appear, first throw away suffix, then reverse, then throw prefix
	
	if (best >= 10000) best = -1;
	return best;
}

};
