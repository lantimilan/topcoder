class Solution {
public:
    vector<string> comb(const string &digits, int pos) {
        const char *table[] = {
            "",  // 0
            "",  // 1
            "abc",  // 2
            "def",  // 3
            "ghi",  // 4
            "jkl",  // 5
            "mno",  // 6
            "pqrs",  // 7
            "tuv",  // 8
            "wxyz",  // 9
        };
        
        vector<string> ans;
        if (pos >= digits.length()) {
            ans.push_back("");
            return ans;
        }
        vector<string> sub = comb(digits, pos+1);
        int d = digits[pos] - '0';
        for (const char *ch = table[d]; *ch; ++ch) {
            for (int i=0; i<sub.size(); ++i) {
                string s; s+=*ch; s+=sub[i];
                ans.push_back(s);
            }
        }
        return ans;
    }
    vector<string> letterCombinations(string digits) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return comb(digits, 0);        
    }
};