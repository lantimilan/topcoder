#include <vector>
using namespace std;

class ShoutterDiv2
{
public:

int count(vector <int> s, vector <int> t)
{
	int cnt = 0;
	for (int i = 0; i < s.size(); ++i)
	for (int j = i+1; j < s.size(); ++j)
	{
		if (t[i] < s[j] || t[j] < s[i]) {}
		else cnt++;
	}
	return cnt;
}
};
