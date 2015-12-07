#include <vector>
#include <string>
#include <iostream>
using namespace std;

string encode(vector < int > p, int k, string s) {
    int n = p.size();
    for (int i = 0; i < n; ++i) { p[i]--; }
    vector<int> inv(n);
    for (int i = 0; i < n; ++i) { inv[p[i]] = i; }

    string ans = s;
    for (int i = 0; i < n; ++i) {
        vector<int> cnt(n, 0);
        vector<int> vec;
        int pos;
        for (pos = i;;pos = inv[pos]) {
            vec.push_back(pos);
            cnt[pos]++;
            if (cnt[pos] > 1) { // found cycle
                break;
            }
        }
        int x;
        for (x = vec.size()-2; x >= 0 && vec[x] != pos; --x)
            ;
        //assert(x >= 0 && vec[x] == pos);
        int cycle = vec.size() -1 - x;
        int num_op = k % cycle;

        int last = i;
        for (int x = 0; x < num_op; ++x) {
            last = inv[last];
        }
        ans[last] = s[i];
    }
    return ans;
}

int main() {
    vector<int> p = {2, 3, 1};
    int k = 2;
    string s = "tom";
    cout << encode(p, k, s) << endl;
}
