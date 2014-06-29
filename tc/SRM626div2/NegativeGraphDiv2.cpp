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

long long dp[1005][55];
const long long INF = 1e9;

class NegativeGraphDiv2 {
public:
	long long findMin(int N, vector <int> s, vector <int> t, vector <int> weight, int charges) {
        vector<map<int, int> > minedge(N), maxedge(N);
        // build graph
        for (int i = 0; i < s.size(); ++i) {
            int start = s[i], end = t[i]; --start, --end;
            int w = weight[i];
            if (minedge[start].count(end)) {
                chmin(minedge[start][end], w);
            } else {
                minedge[start][end] = w;
            }
            if (maxedge[start].count(end)) {
                chmax(maxedge[start][end], w);
            } else {
                maxedge[start][end] = w;
            }
        }

        for (int i = 0; i < N; ++i)
        for (int c = 0; c <= charges; ++c) {
            dp[c][i] = INF;
        }

        dp[charges][0] = 0;
        for (int c = charges; c >= 0; --c) {
            // update without magic, dijkstra
            vector<long long> vec(N);  // cost
            vector<int> used(N);
            for (int i = 0; i < N; ++i) {
                vec[i] = dp[c][i];
                used[i] = 0;
            }
            for (int r = 0; r < N; ++r) {
                int pos = -1;
                for (int p = 0; p < N; ++p) if (!used[p]) {
                    if (pos < 0 || vec[p] < vec[pos]) pos = p;
                }
                long long cost = vec[pos]; used[pos] = true;
                const map<int,int> &nextlist = minedge[pos];
                map<int,int>::const_iterator it;
                for (it = nextlist.begin(); it != nextlist.end(); ++it) {
                    int next = it->first;
                    int w = it->second;
                    chmin(vec[next], cost + w);
                }
            }
            for (int i = 0; i < N; ++i) dp[c][i] = vec[i];
            // update use magic once
            for (int i = 0; i < N; ++i)
            if (c > 0 && dp[c][i] < INF) {
            const map<int,int> &maxnextlist = maxedge[i];
            map<int,int>::const_iterator it;
            for (it = maxnextlist.begin(); it != maxnextlist.end(); ++it) {
                int next = it->first;
                int w = it->second;
                if (c > 0) {
                    chmin(dp[c-1][next], dp[c][i] - w);
                }
            }
            }
        }
        long long ans = INF;
        for (int c = 0; c <= charges; ++c) {
            chmin(ans, dp[c][N-1]);
        }
        return ans;
	}

    template<class T>
    void chmin(T &a, T b) { if (a > b) a = b; }
    template<class T>
    void chmax(T &a, T b) { if (a < b) a = b; }

};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, vector <int> p2, vector <int> p3, int p4, bool hasAnswer, long long p5) {
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
	NegativeGraphDiv2 *obj;
	long long answer;
	obj = new NegativeGraphDiv2();
	clock_t startTime = clock();
	answer = obj->findMin(p0, p1, p2, p3, p4);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p5 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
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
	int p4;
	long long p5;

	{
	// ----- test 0 -----
	p0 = 3;
	int t1[] = {1,1,2,2,3,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,3,1,3,1,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {1,5,1,10,1,1};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1;
	p5 = -9ll;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 1 -----
	p0 = 1;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {100};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 1000;
	p5 = -100000ll;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 2 -----
	p0 = 2;
	int t1[] = {1,1,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,2,1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {6,1,4};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 2;
	p5 = -9ll;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, true, p5) && all_right;
	// ------------------
	}

	{
	// ----- test 3 -----
	p0 = 2;
	int t1[] = {1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	int t3[] = {98765};
			p3.assign(t3, t3 + sizeof(t3) / sizeof(t3[0]));
	p4 = 100;
	p5 = -98765ll;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, true, p5) && all_right;
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
