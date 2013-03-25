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
            if (points.size() == N) {  // all nodes in path
                vector<int> tmp(points.size() - 2);
                copy(++points.begin(), --points.end(), tmp.begin());
                if (cross(points[0], points[N-1], tmp)) { ans++; }
                k = N+1;  // terminate this search path
            } else {
                // look for next node in path
                for (++k; k <= N; ++k) if (!inuse[k]) {
                vector<int> tmp = points; tmp.pop_back();

                bool good = cross(node, k, tmp);
                if (good) { points.push_back(k); inuse[k] = 1; break; }
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
    
 
}; 



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
