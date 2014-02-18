#include <string>
using namespace std;


class MagicalStringDiv2
{
public:

int minimalMoves(string S)
{
	int n = S.size();
	int cost = 0;
	for (int i = 0; i < n / 2; ++i) {
		if (S[i] == '<') cost++;
		if (S[n-1-i] == '>') cost++;
	}
	return cost;
}
};
