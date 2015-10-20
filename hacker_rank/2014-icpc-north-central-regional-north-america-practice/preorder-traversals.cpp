// preorder-traversals.cpp
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

bool solve(const vector<int> &vec, int begin, int end) {
    if (begin >= end) return true;
    int root = vec[begin];
    int l1 = begin + 1;
    int l2;
    for (l2 = l1; l2 < end && vec[l2] < root; ++l2) {
    }
    if (!solve(vec, l1, l2)) return false;
    for (int r = l2; r < end; ++r) {
        if (vec[r] <= root) return false;
    }
    return solve(vec, l2, end);
}

int main() {
    int tcase = 0;
    int a;
    while (cin >> a) {
        vector<int> vec; vec.push_back(a);
        while (cin >> a && a > 0) {
            vec.push_back(a);
        }
        //ostream_iterator<int> out_it(cout, ", ");
        //copy(vec.begin(), vec.end(), out_it);
        cout << "Case " << (++tcase) << ": ";
        bool ans = solve(vec, 0, vec.size());
        cout << (ans ? "yes" : "no") << endl;
    }
}
