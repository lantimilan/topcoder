#include <vector>
using namespace std;

class EllysNumberGuessing
{
public:

bool is_valid(int k)
{
	return 1 <= k && k <= 1000000000;
}

// after first guess, only two possible choices
int getNumber(vector <int> guesses, vector <int> answers)
{
	int res[2];
	res[0] = guesses[0] + answers[0];
	res[1] = guesses[0] - answers[0];
	
	for (int i = 1; i < guesses.size(); ++i) {
		int cur[2];
		cur[0] = guesses[i] + answers[i];
		cur[1] = guesses[i] - answers[i];
		
		if (res[0] == cur[0] || res[0] == cur[1]) {}
		else res[0] = -100;
		
		if (res[1] == cur[0] || res[1] == cur[1]) {}
		else res[1] = -100;
	}
	if (is_valid(res[0]) && is_valid(res[1])) return -1;
	if (is_valid(res[0])) return res[0];
	if (is_valid(res[1])) return res[1];
	return -2;
}
};
