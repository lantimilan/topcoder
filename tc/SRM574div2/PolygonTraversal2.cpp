#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;

#define fort(i,a) for(typeof a.begin() i=a.begin(); i!=a.end(); ++i)
#define sz(a) int(a.size())

class PolygonTraversal2
{ 
public: 
    bool inrange(int lo, int hi, int val)
    {
//    cout << "inrange " << lo << ' ' << hi << ' ' << val << endl;
        assert(lo < hi);
        return (lo < val && val < hi);
    }

    bool intersect(int a, int b, int c, int d)
    {
        int x, y;
        x = min(a, b); y = max(a, b);
        bool ans1 = inrange(x, y, c) && !inrange(x, y, d);
        bool ans2 = !inrange(x, y, c) && inrange(x, y, d);
        return ans1 || ans2;
    }

    int count(int N, vector <int> points) 
    { 
        int start = points.size();
        int neighbor[20] = {0};
        int inuse[20] = {0};
        for (int i = 0; i < points.size(); ++i)
            inuse[points[i]] = 1;

        int ans = 0;
        while (points.size() >= start) {
            int node = points.back();
            int k = neighbor[node];
            for (++k; k <= N; ++k) if (node != k) {
                bool good = false;
                for (int j = 0; j+2 < points.size(); ++j) {
                    if (k != points[j] && k != points[j+1] && intersect(node, k, points[j], points[j+1])) {
                        good = true; break;
                    }
                }
                if (!good) continue;
                if (k == points[0] && points.size() == N) {
                    // terminal state
                    ans++;
                    k = N+1;
                    break;
                } else if (!inuse[k]) {
                    points.push_back(k);
                    inuse[k] = 1;
                    break;
                }
            }
            if (k > N) {
                points.pop_back();
                inuse[node] = 0;
                neighbor[node] = 0;
            } else {
                neighbor[node] = k;
            }
        }
        return ans;
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1, 3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arr1[] = {1, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 7; int Arr1[] = {2, 4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {1, 2, 3, 4, 6, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 11; int Arr1[] = {1, 5, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1412; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    PolygonTraversal2 __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
