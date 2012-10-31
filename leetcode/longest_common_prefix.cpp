class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        string ans;
        if (strs.empty()) return ans;
        for (int p=0; p < strs[0].length(); ++p) {
            char ch = strs[0][p];
            bool match = true;
            for (int i=1; i < strs.size(); ++i) {
                if (p >= strs[i].length() || strs[i][p] != ch) {
                    match = false; break;
                }
            }
            if (match) ans += ch;
            else break;
        }
        return ans;
    }
};

// an easy one