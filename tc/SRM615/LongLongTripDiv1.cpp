#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// 1. if T is small, then the problem is easy
// let (dist, node) be true if there is a walk from node[0] to that node with total length = dist
// then we can compute dp[dist][node] for all dist=0..T and node=0..N-1
// but here T is rather large, 10^18
//
// 2. the way to get around T is, instead of dp[dist][node], we reduce the space to dp[dist % d][node]
// where d is 2*edge[0][i] for some node[i], use edge[N-1][i] will also work.
// now we define dp[dist % d][node] be the shortest length of a walk starting at node[0], ending at node,
// with total length % d = dist % d.
// Then we are looking at dp[T % d][N-1]
// we know dp[T % d][N-1] must be <= T if there is a walk from node[0] to node[N-1] with length T
// if this walk has length < T, then T - length is divisible by d, so we can prepend this walk by d, that
// is, we can use a loop of length d from node[0] to its neighbor that defines d.
//
// total number of state is 2*D[i] * N = 2 * 10^4 * 50 = 10^6
// at most 50 edges so each state has at most 50 next states to update
// because all transitions are with a positive edge, we can use dijkstra's algorithm

struct edge {
    int next;
    int length;
    edge(int nn, int ll) {
        next = nn; length = ll;
    }
};

typedef pair<int, int> PII;  // rem, node
typedef pair<long long, PII> PLL;

long long dist[20000+5][55];
priority_queue<PLL> que;

class LongLongTripDiv1 {
public:
	string isAble(int N, vector <int> A, vector <int> B, vector <int> D, long long T) {
        const string possible = "Possible";
        const string impossible = "Impossible";
        int modulo = -1;
        int M = A.size();
        vector<vector<edge> > graph(N);
        for (int i = 0; i < M; ++i) {
            int a = A[i], b = B[i], d = D[i];
            graph[a].push_back(edge(b, d));
            graph[b].push_back(edge(a, d));
            if (a == 0 || b == 0) modulo = 2*d;
        }
        if (modulo < 0) return impossible;

        for (int d = 0; d < modulo; ++d)
        for (int i = 0; i < N; ++i)
            dist[d][i] = T+1;

        dist[0][0] = 0;
        que.push(make_pair(0, make_pair(0, 0)));
        while (!que.empty()) {
            PLL elem = que.top(); que.pop();
            long long cost = -elem.first;
            int rem = elem.second.first;
            int node = elem.second.second;
            if (dist[rem][node] != cost) continue;  // skip because (rem,node) already processed with a better dist
            for (int i = 0; i < graph[node].size(); ++i) {
                int next = graph[node][i].next;
                int length = graph[node][i].length;
                int newrem = (rem + length) % modulo;
                int newcost = cost + length;
                if (update(dist[newrem][next], newcost))
                    que.push(make_pair(-newcost, make_pair(newrem, next)));
            }
        }
        while (!que.empty()) que.pop();
        if (dist[T % modulo][N-1] <= T) return possible;
        else return impossible;
	}

    bool update(long long &a, long long b) {
        if (a > b) { a = b; return true; }
        else return false;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, vector <int> p2, vector <int> p3, long long p4, bool hasAnswer, string p5) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p3.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p3[i];
	}
	cout << "}" << "," << p4;
	cout << "]" << endl;
	LongLongTripDiv1 *obj;
	string answer;
	obj = new LongLongTripDiv1();
	clock_t startTime = clock();
	answer = obj->isAble(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p5 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p5;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;

	int p0;
	vector <int> p1;
	vector <int> p2;
	vector <int> p3;
	long long p4;
	string p5;

	{
	// ----- test 0 -----
	p0 = 3;
	int t1[] = {0,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,1,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {7,6,5};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 11ll;
	p5 = "Possible";
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	p0 = 3;
	int t1[] = {0,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,1,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {7,6,5};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 25ll;
	p5 = "Possible";
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	p0 = 2;
	int t1[] = {0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {1};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 9ll;
	p5 = "Possible";
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	p0 = 2;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {0};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {1};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1000000000000000000ll;
	p5 = "Impossible";
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 4 -----
	p0 = 4;
	int t1[] = {0,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,1,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {10,10,10};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1000ll;
	p5 = "Impossible";
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 5 -----
	p0 = 9;
	int t1[] = {4,8,5,8,3,6,2,6,7,6,6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,7,1,5,1,3,1,1,5,4,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {6580,8822,1968,673,1394,9337,5486,1746,5229,4092,195};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 937186357646035002ll;
	p5 = "Impossible";
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
//SRM615div1p500
