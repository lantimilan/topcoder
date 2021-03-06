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

// the problem is actually 1-dim
// from (0,0) -> (1,1) -> (2,2) -> ... -> (0,0)
// these are the only nodes reachable from (0,0)
//
// now relabel them to 0, 1, 2, ..., d
// then E[0] = 0
// E[1] = 1 + .5 * E[0] + .5 * E[2]
// E[2] = 1 + .5 * E[1] + .5 * E[3]
// ...
// E[d] = 1 + .5 * E[d-1] + .5 * E[0]
//
// due to symmetry, E[1] = E[d]
// if we add all these equations, we get E[1] + E[d] = d + .5 * E[0] + .5 * E[d]
// then E[1] = 1*d
// then we can solve E[2] = 2*(d-1)
// E[3] = 3*(d-2)
// ...

class TorusSailingEasy {
public:
	double expectedTime(int N, int M, int goalX, int goalY) {
        int d = 0;
        int pos = 0;
        int x = 0, y = 0;
        while (true) {
            x = (x+1) % N;
            y = (y+1) % M;
            if (x == 0 && y == 0) break;
            d++; if (x == goalX && y == goalY) pos = d;
        }
        if (pos == 0) return -1;
        return pos * (d+1 - pos);
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, bool hasAnswer, double p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3;
	cout << "]" << endl;
	TorusSailingEasy *obj;
	double answer;
	obj = new TorusSailingEasy();
	clock_t startTime = clock();
	answer = obj->expectedTime(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p4 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = fabs(p4 - answer) <= 1e-9 * max(1.0, fabs(p4));
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
	int p1;
	int p2;
	int p3;
	double p4;

	{
	// ----- test 0 -----
	p0 = 2;
	p1 = 2;
	p2 = 1;
	p3 = 1;
	p4 = 1.0;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	p0 = 2;
	p1 = 2;
	p2 = 0;
	p3 = 1;
	p4 = -1.0;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	p0 = 3;
	p1 = 3;
	p2 = 1;
	p3 = 1;
	p4 = 2.0;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	p0 = 4;
	p1 = 6;
	p2 = 1;
	p3 = 3;
	p4 = 27.0;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) && all_right;
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
