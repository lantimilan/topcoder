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

string nextperm[55][55][55];
string minperm[55][55];
int caneq[55][55][55];
string a, b;

class LeftRightDigitsGame2
{ 
public: 
    int calceq(int la, int ra, int lb, int rb) {
        assert(ra-la == rb-lb);
        if (la==ra) return 1; // basecase, empty string
        int &ans = caneq[la][ra][lb];
        if (ans >= 0) return ans;
        else {
            int x1, x2;
            x1 = x2 = 0;
            if (a[ra-1] == b[rb-1]) x1 = calceq(la, ra-1, lb, rb-1);
            if (a[ra-1] == b[lb]) x2 = calceq(la, ra-1, lb+1, rb);
            return ans = (x1 || x2);
        }
    }

    string getmin(int la, int ra) {
        if (la==ra) return "";
        if (ra-la == 1) return a.substr(la,1);
        string &ans = minperm[la][ra];
        if (ans != "") return ans;
        for(int j=la; j<ra; ++j) {
            string tmp;
            tmp += a[j];
            tmp += getmin(la, j);
            if (j+1<ra) tmp += a.substr(j+1, ra-j-1);
            if (ans == "" || tmp < ans) ans = tmp;
        }
        return ans;
    }

    string calcperm(int la, int ra, int lb, int rb) {
        if (ra-la == 1) {
            if (a[la] > b[lb]) { return a.substr(la,1); }
            else return "";
        }
        string &ans = nextperm[la][ra][lb];
        if (ans == "" || ans[0] != 'X') return ans;
        ans = "";
        for(int j=la; j < ra; ++j) {
            if (a[j] > b[lb]) {
                string tmp="";
                if (la<j) tmp = getmin(la, j);
                tmp = a.substr(j,1) + tmp;
                if (j+1<ra) tmp += a.substr(j+1, ra-j-1);
                if (ans == "" || tmp < ans) ans = tmp;
            } else if (a[j] == b[lb]) {
                string tmp;
                if (j+1<ra) {
                    if (a.substr(j+1, ra-j-1) > b.substr(rb-(ra-j-1),ra-j-1)) {
                        if (calceq(la, j, lb+1, lb+1+j-la)) {
                            tmp = b.substr(lb, j+1-la) + a.substr(j+1, ra-j-1);
                        } else {
                            tmp = calcperm(la, j, lb+1, lb+1 + j-la);
                            if (tmp != "")
                                tmp = a.substr(j,1) + tmp + a.substr(j+1, ra-j-1);
                        }
                    } else {
                        tmp = calcperm(la, j, lb+1, lb+1 + j-la);
                        if (tmp != "")
                            tmp = a.substr(j,1) + tmp + a.substr(j+1, ra-j-1);
                    }
                } else { // j+1..ra is empty
                    tmp = calcperm(la, j, lb+1, lb+1 + j-la);
                    if (tmp!="")
                        tmp = a.substr(j,1) + tmp;
                }
                if (tmp != "")
                    if (ans == "" || tmp < ans) ans = tmp;
            }
        }
        //cerr << la << ' ' << ra << ' ' << lb << ' ' << rb
        //     << ' ' << ans << endl;
        return ans;
    }

    string minNumber(string _a, string _b) 
    { 
        a = _a; b = _b;
        memset(caneq, -1, sizeof caneq);
        int n = a.size();
        for(int i=0; i<=n; ++i)
        for(int j=0; j<=n; ++j)
            minperm[i][j] = "";
        for(int i=0; i<=n; ++i)
        for(int j=0; j<=n; ++j)
        for(int k=0; k<=n; ++k)
        for(int l=0; l<=n; ++l)
            nextperm[i][j][k] = "X";
        if (calceq(0, n, 0, n)==1) return b;
        else {
            return calcperm(0, n, 0, n);
        }
    } 
    
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; string Arg2 = "556"; verify_case(0, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "565"; string Arg1 = "566"; string Arg2 = "655"; verify_case(1, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "565"; string Arg1 = "656"; string Arg2 = ""; verify_case(2, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "9876543210"; string Arg1 = "5565565565"; string Arg2 = "5678943210"; verify_case(3, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "8016352"; string Arg1 = "1000000"; string Arg2 = "1086352"; verify_case(4, Arg2, minNumber(Arg0, Arg1)); }

// END CUT HERE
 
}; 

// BEGIN CUT HERE 
int main()
{
    LeftRightDigitsGame2 __test; 
    __test.run_test(-1); 
} 
// END CUT HERE 
