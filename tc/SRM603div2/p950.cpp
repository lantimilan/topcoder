#include <vector>
#include <string>
using namespace std;

// Claim:
// optimal move is a chain ended with a self-loop of one node
//
// each node can stay, or move to another node
// prob[i][t] be the winning probability starting at node i for t steps,
// then we can do enough iterations till more rounds does not make a difference
//
// prob[i][t+1] = (winprob[i] + (1 - winprob[i] - loseprob[i]) * max prob[j][t] where (i,j) is an edge) 
// that is, i can move into j
// prob[i][0] = 0
//
// how many steps suffices: 0.99^2000 = 1.86e-9, and 0.99^3000 = 8e-14
// so 3000 steps are enough

class GraphWalkWithProbabilities
{
public:

template<class T>
void update(T &a, T b)
{
	if (a < b) a = b;
}

double findprob(vector <string> graph, vector <int> winprob, vector <int> loseprob, int Start)
{
	double prob[55];
	int n = graph.size();
	for (int i = 0; i < n; ++i) {
		prob[i] = 1.0 * winprob[i] / (winprob[i] + loseprob[i]);
	}
	for (int len = 0; len < n-1; ++len) {
		for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) if (graph[i][j] == '1') {
			double remprob = 1.0 - (winprob[i] + loseprob[i]) / 100.0;
			double curprob = winprob[i] / 100.0 + remprob * prob[j];
			update(prob[i], curprob);
		}
	}
	double maxprob = 0.0;
	for (int i = 0; i < n; ++i) if (graph[Start][i] == '1') {
		update(maxprob, prob[i]);
	}
	return maxprob;
}
};
