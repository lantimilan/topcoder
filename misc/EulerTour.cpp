// EulerTour.cpp
//
// recursive call on euler_tour(start) will eventually reach a call
// euler_tour(start) to the same node, that is, start
// at this point we found a cycle (start..start),
// then we can recurse on nodes in this cycle to complete the euler tour
// Notice that nodes in tour are arranged as a stack
// the actual tour is obtained by popping nodes out of stack
// a call to euler_tour(node) results in a segment of (node..node),
// which is a cycle to be pushed to the stack
// base case is when node has no out-going edges, in which case we
// have a trivial cycle of only one node, and the segment pushed is
// (node), a one element segment

#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;

stack<int> tour;
vector<vector<int> > graph;
map<pair<int,int>, int> mark;
map<pair<int,int>, int> edge_hits;


void euler_tour(int start)
{
    for (int x = 0; x < graph[start].size(); ++x) {
        int next = graph[start][x];
        if (!mark[make_pair(start,next)]) {
            mark[make_pair(start,next)] = 1;
            euler_tour(next);
        }
    }
    tour.push(start);
}

void print(stack<int> my_tour) {
    while (!my_tour.empty()) {
        int top = my_tour.top(); cout << top << ' ';
        my_tour.pop();
    }
}

// return true if every edge has been visited exactly once
bool validate(stack<int> my_tour)
{
    assert(!my_tour.empty());
    int first = my_tour.top(); my_tour.pop();
    while (!my_tour.empty()) {
        int second = my_tour.top(); my_tour.pop();
        pair<int,int> p = make_pair(first, second);
        if (edge_hits.count(p) && edge_hits[p] == 0) {
            edge_hits[p] = 1;
        } else {
            return false;
        }
        first = second;
    }
    map<pair<int,int>, int>::iterator it;
    for (it = edge_hits.begin(); it != edge_hits.end(); ++it) {
        if (it->second == 0) return false;  // edge not visited
    }
    return true;
}

void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    graph.clear();
    mark.clear();
    edge_hits.clear();
    assert(tour.empty());

    int N; cin >> N;
    int M; cin >> M;
    graph.resize(N);
    for (int j = 0; j < M; ++j) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        mark[make_pair(a,b)] = 0;
        edge_hits[make_pair(a,b)] = 0;
    }
    int start = 0;
    euler_tour(start);
    assert(validate(tour));  // validate tour is Euler
    print(tour); cout << endl;
    // clear tour
    while (!tour.empty()) tour.pop();
}


int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
