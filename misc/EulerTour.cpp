// EulerTour.cpp
//

#include <iostream>
#include <map>
#include <vector>
using namespace std;

vector<int> tour;
vector<vector<int> > graph;
map<pair<int,int>, int> mark;

void euler_tour(int start)
{
    tour.push_back(start);
    int next = -1;
    for (int x = 0; x < graph[start].size(); ++x) {
        int next = graph[start][x];
        if (!mark[make_pair(start,next)]) {
            mark[make_pair(start,next)] = 1;
            euler_tour(next);
        }
    }
}


void solve(int tcase)
{
    cout << "Case #" << tcase << ": ";
    tour.clear();
    graph.clear();
    mark.clear();
    int N; cin >> N;
    int M; cin >> M;
    graph.resize(N);
    for (int j = 0; j < M; ++j) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        mark[make_pair(a,b)] = 0;
    }
    int start = 0;
    euler_tour(start);
    for (int i = 0; i < tour.size(); ++i) {
        if (i) cout << ' ';
        cout << tour[i];
    }
    cout << endl;
}

int main()
{
    int T; cin >> T;
    for (int t = 1; t <= T; ++t)
        solve(t);
}
