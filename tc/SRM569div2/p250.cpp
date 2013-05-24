#include <vector>
using namespace std;


class TheJediTestDiv2
{
public:
// try Y on 0 to N-1 floors and find the min
int countSupervisors(vector <int> students, int Y, int J)
{
	int N = students.size();
	int best = 2000 * N;
	for (int i = 0; i < N; ++i) {
		int curr = 0;
		int rem = max(0, students[i] - Y);
		curr += (rem + J-1) / J;
		for (int j = 0; j < N; ++j) if (j != i) {
			curr += (students[j] + J-1) / J;
		}
		best = min(best, curr);
	}
	return best;
}
};
