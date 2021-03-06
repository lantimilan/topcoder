#include <cstring>
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

// dp[i][mask][j] is number of ways to use only the first i cards
// with second form mask and number of distinct integer being j
//
// base case: dp[0][0][0] = 1
// update:
// from dp[i][mask][j], to process first[i] and second[i]
// if we use cards[i], 0-based
// then next state is dp[i+1][mask | 1<<second[i]][j+1 or j+2]
// else we do not use cards[i]
// then next state is dp[i+1][mask][j]
long long dp[55][1<<10][55];

class TaroCards {
public:
	long long getNumber(vector <int> first, vector <int> second, int K) {
    // must sort because then we can remember whether we have seen 1..i
        memset(dp, 0, sizeof dp);
        vector<pair<int,int> > vpp(first.size());
        for (int i = 0; i < first.size(); ++i) {
            vpp[i] = make_pair(first[i], second[i]);
        }
        sort(vpp.begin(), vpp.end());
        dp[0][0][0] = 1;  // mask is 1<<0
        for (int i = 0; i < first.size(); ++i) {
            for (int mask = 0; mask < (1<<10); ++mask)
            for (int j = 0; j <= 50; ++j) {
                // use cards[i]
                int card1 = vpp[i].first;
                int card2 = vpp[i].second;
                int newmask = mask;
                int j2 = j;

                if (1LL << (card1-1) & newmask) {}
                else { j2++; if (card1 <= 10) newmask |= 1 << card1-1; }

                if (1 << card2-1 & newmask) {}
                else { j2++; newmask |= 1 << card2-1; }

                if (j2 > 50) continue;
                dp[i+1][newmask][j2] += dp[i][mask][j];
                // do not use cards[i]
                dp[i+1][mask][j] += dp[i][mask][j];
            }
        }
        int n = first.size();
        long long ans = 0;
        for (int mask = 0; mask < (1<<10); ++mask)
        for (int d = 0; d <= min(50, K); ++d) {
            ans += dp[n][mask][d];
            //cout << n << ' ' << mask << ' ' << d << ' ' << dp[n][mask][d] << endl;
        }
        return ans;
	}
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, int p2, bool hasAnswer, long long p3) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << p2;
	cout << "]" << endl;
	TaroCards *obj;
	long long answer;
	obj = new TaroCards();
	clock_t startTime = clock();
	answer = obj->getNumber(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p3;
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

	vector <int> p0;
	vector <int> p1;
	int p2;
	long long p3;

	{
	// ----- test 0 -----
	int t0[] = {1,2};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 2;
	p3 = 3ll;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	int t0[] = {3,1,2};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {1,1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = 8ll;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	int t0[] = {4,2,1,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {1,2,3,4};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 5;
	p3 = 16ll;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	int t0[] = {1,2,3,4,5,6,7};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,1,10,9,3,2,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = 17ll;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 4 -----
	int t0[] = {1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 1;
	p3 = 1ll;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}

	{
	// ----- test 5 -----
	int t0[] = {6,20,1,11,19,14,2,8,15,21,9,10,4,16,12,17,13,22,7,18,3,5};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {4,5,10,7,6,2,1,10,10,7,9,4,5,9,5,10,10,3,6,6,4,4};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 14;
	p3 = 2239000ll;
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, true, p3) && all_right;
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
