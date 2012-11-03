class Solution {
public:
    bool attack(const vector<int> &pre, int c) {
        int r = pre.size();
        for (int i=0; i<r; ++i) {
            if (r - i == abs(c - pre[i])) return true;
        }
        return false;            
    }
    void genperm(vector<int> &pre, vector<int> &rest, int &ans) {
        if (rest.empty()) { ++ans; return; }
        for (int i=0; i<rest.size(); ++i) {
            if (!attack(pre, rest[i])) {
                int n = rest.size();                
                swap(rest[i], rest[n-1]);
                pre.push_back(rest.back()); rest.pop_back();
                genperm(pre, rest, ans);
                rest.push_back(pre.back()); pre.pop_back();
                swap(rest[i], rest[n-1]);
            }
        }
    }
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ans = 0;
        // gen all permutations and do pruning
        vector<int> pre, cols(n);
        for (int i=0; i<n; ++i) cols[i] = i;
        genperm(pre, cols, ans);  // cannot use temp like vector<int>() in place of pre
        // because c++ thinks a temp is rval and cannot be used as lval
        return ans;
    }
};
