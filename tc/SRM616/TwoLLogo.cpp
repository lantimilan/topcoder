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
#include <cstring>
#include <cassert>

using namespace std;

// fix the first L
// then solve the second
class TwoLLogo {
public:
	long long countWays(vector <string> grid) {
        long long ans = 0LL;
        int N = grid.size();
        int M = grid[0].size();
        for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[i].size(); ++j)
        for (int up = 1; up < N; ++up)
        for (int rr = 1; rr < M; ++rr)
        {
            int top = i - up;
            int right = j + rr;
            if (top >= 0 && right < M) {
                bool good = true;
                for (int r1 = i; r1 >= top; --r1)
                    if (grid[r1][j] == '#') good = false;
                for (int c1 = j; c1 <= right; ++c1)
                    if (grid[i][c1] == '#') good = false;
                if (good) {
                    vector<string> grid2 = grid;
                    for (int r1 = i; r1 >= top; --r1)
                        grid2[r1][j] = '#';
                    for (int c1 = j; c1 <= right; ++c1)
                        grid2[i][c1] = '#';
                    ans += calc(grid2);
                }
            }
        }
        assert(ans % 2 == 0);
        return ans / 2;
	}

    long long calc(const vector<string> &grid) {
        int N = grid.size();
        int M = grid[0].size();
        // process row
        int forward[32][32]; memset(forward, -1, sizeof forward);
        int upward[32][32]; memset(upward, -1, sizeof upward);
        for (int i = 0; i < N; ++i) {
            int last = -1;
            for (int j = M-1; j >= 0; --j) {
                if (last >= 0) {
                    if (grid[i][j] == '.') forward[i][j] = last;
                    else last = -1;
                } else {
                    if (grid[i][j] == '.') last = j;
                }
            }
        }
        for (int j = 0; j < M; ++j) {
            int last = -1;
            for (int i = 0; i < N; ++i) {
                if (last >= 0) {
                    if (grid[i][j] == '.') upward[i][j] = last;
                    else last = -1;
                } else {
                    if (grid[i][j] == '.') last = i;
                }
            }
        }
        long long ans = 0LL;
        for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
        if (forward[i][j] >= 0 && upward[i][j] >= 0)
        {
            long long a = forward[i][j] - j;
            long long b = i - upward[i][j];
            ans += a * b;
        }
        return ans;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, long long p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	TwoLLogo *obj;
	long long answer;
	obj = new TwoLLogo();
	clock_t startTime = clock();
	answer = obj->countWays(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
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

	vector <string> p0;
	long long p1;

	{
	// ----- test 0 -----
	string t0[] = {"....","...."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1ll;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	string t0[] = {".##..","...#.",".#.#.","#...#"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3ll;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	string t0[] = {"..#.","#.#.","....","..#."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4ll;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	string t0[] = {"..",".."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 0ll;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 4 -----
	string t0[] = {".#.#","....",".#.#","...."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 34ll;
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 5 -----
	string t0[] = {"##############","##############","#.############","#.############","#.############","#.############","#.############","#.############","#.#####.######","#.#####.######","#.#####.######","#....##.######","#######.######","#######.######","#######.######","#######.######","#######.######","#######.######","#######......#","##############"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1350ll;
	all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 6 -----
	string t0[] = {"#......",".#....#",".#.#...","#....#.",".##..#.",".#.....",".....#.",".#.#...",".#...#.","..##..."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2386ll;
	all_right = KawigiEdit_RunTest(6, p0, true, p1) && all_right;
	// ------------------
	}

	{
	// ----- test 7 -----
	string t0[] = {"...#..........................","..............................","..............................","..................#...#.......","..................#...........","..............................","...........#..................","..............................",".....#..#.....................",".......................#......","..................#.....#.....","..............................","..............................","..............................","..............................","..#...........................","..............................","..............................","..............................","#............................#","..............................",".....#.........#............#.","..............................",".........................#....",".#............................",".............#................","..............................","..............................",".......................#......",".............#................"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 5020791386ll;
	all_right = KawigiEdit_RunTest(7, p0, true, p1) && all_right;
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
