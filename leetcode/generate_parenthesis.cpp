class Solution {
public:
    vector<string> generateParenthesis(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return gen(n);
    }
    vector<string> gen(int n) {
        vector<string> ans;
        if (n==0) {
            ans.push_back("");
            return ans;
        }
        vector<string> left, right;
        for (int l=0; l<n; ++l) {
            int r = n-l-1;
            left = gen(l);
            right = gen(r);
            for (int i=0; i<left.size(); ++i)
            for (int j=0; j<right.size(); ++j)
            {
                string s;
                s += '(';
                s += left[i];
                s += ')';
                s += right[j];
                ans.push_back(s);
            }
        }
        return ans;
    }
};