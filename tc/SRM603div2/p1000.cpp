#include <vector>
#include <string>
using namespace std;
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

double prob[55][3005];

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
/*
	for (int i = 0; i < graph.size(); ++i) {
		prob[i][1] = 1.0 * winprob[i] / (winprob[i] + loseprob[i]);
	}*/
	for (int t = 1; t <= 3000; ++t) {
		for (int i = 0; i < graph.size(); ++i) {
			for (int j = 0; j < graph[i].size(); ++j) if (graph[i][j] == '1') {
				double remprob = 1.0 - (winprob[i] + loseprob[i]) / 100.0;
				update(prob[i][t], 0.01 * winprob[i] + remprob * prob[j][t-1]);
			}
		}
	}
	double maxprob = 0.0;
	for (int i = 0; i < graph.size(); ++i)
		if (graph[Start][i] == '1')
			update(maxprob, prob[i][3000]);
	return maxprob;
}
};
