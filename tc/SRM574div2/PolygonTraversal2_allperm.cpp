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

    bool cross(int a, int b, vector<int> list) {
        for (int i = 0; i+1 < list.size(); ++i) {
            if (intersect(a, b, list[i], list[i+1]))
                return true;
        }
        return false;
    }

	// the solution with gen all permutation is much slower than backtracking
	// although easier to code
    int count(int N, vector <int> points) 
    { 
		int ans = 0;
		if (points.size() < 3) return 0;  // careful, 11 factorial TLE
		// generate all permutations, only 13-2=11 factorial
		vector<int> rem;
		for (int i = 1; i <= N; ++i) {
			bool used = false;
			for (int j = 0; j < points.size(); ++j)
				if (points[j] == i) { used = true; break; }
			if (!used) rem.push_back(i);
		}
		sort(rem.begin(), rem.end());
		do {
			bool good = true;
			vector<int> prefix = points; prefix.pop_back();
			for (int i = 0; i <= rem.size(); ++i) {
				int prev, curr;
				if (i == 0) { prev = points.back(); curr = rem[i]; }
				else if (i == rem.size()) { prev = rem.back(); curr = points[0]; }
				else { prev = rem[i-1]; curr = rem[i]; }
				
				if (!cross(prev, curr, prefix)) { good = false; break; }
				prefix.push_back(prev);
				if (prefix.size() >= N-1) prefix.erase(prefix.begin());
			}
			//cout << good << endl;
			if (good) { ans++; }
		} while (next_permutation(rem.begin(), rem.end()));
        return ans;
    } 
    
 
}; 
