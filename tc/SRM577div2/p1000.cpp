#include <vector>
#include <algorithm>
using namespace std;

class EllysCoprimesDiv2
{
public:

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}
int getCount(vector <int> numbers)
{
	int cnt = 0;
	sort(numbers.begin(), numbers.end());
	for (int i = 1; i < numbers.size(); ++i) {
		int curr = -1;
		int a = numbers[i-1], b = numbers[i];
		if (gcd(a,b) == 1) curr = 0;
		else {
			for (int k = a+1; k < b; ++k) if (gcd(a,k) == 1 && gcd(b,k) == 1)
			{ curr = 1; break; }
			if (curr < 0) curr = 2;
		}
		cnt += curr;
	}
	return cnt;
}
};
