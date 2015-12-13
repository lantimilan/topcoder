// goty-and-the-play.cpp
#include <iostream>
#include <multiset>
using namespace std;

map<int,set<int>> scenes;
map<int,int> actors;
multiset<int> cnts;

int main() {
    int M, N, Q; cin >> M >> N >> Q;
    for (int i = 0; i < N; ++i) {
        int target; cin >> target;
        actors[i] = target;
        scenes[target].insert(i);  // check null
    }
    for (auto kv : scenes) {
        cnts.insert(kv.second.size());
    }
    while (Q--) {
        int action; cin >> action;
        if (action == 1) {
            int actor, newhome; cin >> actor >> newhome;
            int home = actors[actor];
            int from = scenes[home].size();
            int to = scenes[newhome].size();
            scenes[home].erase(actor);
            scenes[newhome].insert(actor);
            cnts.erase(cnts.find(from));
            cnts.erase(cnts.find(to));
            cnts.insert(from-1);
            cnts.insert(to+1);
        } else {
            // AVL tree or treap
        }
    }
}
